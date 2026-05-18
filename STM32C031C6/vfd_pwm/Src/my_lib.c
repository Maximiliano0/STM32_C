/* Includes ------------------------------*/
#include "my_lib.h"
#include "stm32c0xx_hal.h"
#include "stm32c0xx_hal_uart.h"
#include <string.h>
#include <stdio.h>

/* ===========================================================================
 *  Estado global
 * ========================================================================= */
TIM_HandleTypeDef  hpwm;
UART_HandleTypeDef hctrl;

/* Parametros DDS modificables desde fuera de la IRQ.
   Son uint32: lectura/escritura atomica en M0+ (bus 32 bits, 1 ciclo). */
static volatile uint32_t dds_phase     = 0;
static volatile uint32_t dds_phase_inc = 0;     /* (fo_mHz << 32) / (fs*1000) */
static volatile uint32_t dds_amp_q15   = 0;     /* 0..32767, valor expuesto al getter */
static volatile uint32_t dds_amp_ccr   = 0;     /* pre-escalado: amp_q15 * (ARR/2) >> 15, en cuentas de CCR */
static volatile uint32_t dds_offset    = 0;     /* 0..PWM_ARR */
static volatile uint32_t dds_fo_mHz    = 0;     /* cacheado para getter */

/* RX por IRQ: cada byte recibido va a un ring de linea.
   ready=1 cuando hay '\n'/'\r' -> el main lo procesa fuera de la IRQ. */
static volatile uint8_t  rx_byte;
static volatile uint8_t  rx_line[CTRL_RX_BUF_LEN];
static volatile uint8_t  rx_idx   = 0;
static volatile uint8_t  rx_ready = 0;

/* ===========================================================================
 *  DDS: nucleo. Llamado desde TIM1 Update IRQ cada periodo PWM (fs = 20 kHz).
 *  Costo aprox: ~15 ciclos Cortex-M0+.
 * ========================================================================= */
static inline void vfd_update_ccr(void)
{
    uint8_t  idx = (uint8_t)(dds_phase >> (32 - WAVE_LUT_BITS));
    int16_t  s   = sine_q15[idx];                          /* Q15 signed: +-32767 */
    /* v en cuentas de CCR: amp_ccr ya viene pre-escalado en el setter,
       asi que aqui solo queda multiplicar por sin (Q15) y bajar 15 bits.
       Para amp_q15 = 32767 y offset = ARR/2  ->  v en [-ARR/2, +ARR/2]
       y por lo tanto ccr en [0, ARR] SIN saturar. */
    int32_t  v   = ((int32_t)s * (int32_t)dds_amp_ccr) >> 15;
    int32_t  ccr = (int32_t)dds_offset + v;
    if      (ccr < 0)             ccr = 0;
    else if (ccr > (int32_t)PWM_ARR) ccr = (int32_t)PWM_ARR;
    PWM_TIMER->CCR1 = (uint16_t)ccr;
    dds_phase      += dds_phase_inc;
}

/* ===========================================================================
 *  Setters / Getters
 * ========================================================================= */
void vfd_set_frequency_mhz(uint32_t fo_mHz)
{
    if (fo_mHz > VFD_FO_MAX_MHZ) fo_mHz = VFD_FO_MAX_MHZ;
    /* phase_inc = fo_mHz * 2^32 / (fs * 1000)
       Uso uint64 intermedio para no perder precision. */
    uint64_t inc = ((uint64_t)fo_mHz << 32) / ((uint64_t)FS_HZ * 1000ULL);
    dds_phase_inc = (uint32_t)inc;
    dds_fo_mHz    = fo_mHz;
}

void vfd_set_amplitude_q15(uint16_t amp_q15)
{
    if (amp_q15 > VFD_AMP_MAX_Q15) amp_q15 = VFD_AMP_MAX_Q15;
    dds_amp_q15 = amp_q15;
    /* Pre-escalado a cuentas de CCR: amp_q15 = 32767 -> swing maximo = PWM_ARR/2.
       Hacerlo aqui (no en la IRQ) evita una multiplicacion por muestra. */
    dds_amp_ccr = ((uint32_t)amp_q15 * (PWM_ARR / 2U)) >> 15;
}

void vfd_set_offset_ccr(uint16_t off_ccr)
{
    if (off_ccr > PWM_ARR) off_ccr = PWM_ARR;
    dds_offset = off_ccr;
}

uint32_t vfd_get_frequency_mhz(void) { return dds_fo_mHz;  }
uint16_t vfd_get_amplitude_q15(void) { return (uint16_t)dds_amp_q15; }
uint16_t vfd_get_offset_ccr   (void) { return (uint16_t)dds_offset;  }

/* ===========================================================================
 *  Inicializacion de hardware
 * ========================================================================= */

void SystemClock_Config(void)
{
    RCC_OscInitTypeDef osc = {0};
    RCC_ClkInitTypeDef clk = {0};

    /* 48 MHz -> el flash necesita 1 WS. Subir latencia antes del switch. */
    __HAL_FLASH_SET_LATENCY(FLASH_LATENCY_1);

    osc.OscillatorType      = RCC_OSCILLATORTYPE_HSI;
    osc.HSIState            = RCC_HSI_ON;
    osc.HSIDiv              = RCC_HSI_DIV1;
    osc.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    HAL_RCC_OscConfig(&osc);

    clk.ClockType      = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;
    clk.SYSCLKSource   = RCC_SYSCLKSOURCE_HSI;
    clk.SYSCLKDivider  = RCC_SYSCLK_DIV1;
    clk.AHBCLKDivider  = RCC_HCLK_DIV1;
    clk.APB1CLKDivider = RCC_APB1_DIV1;
    HAL_RCC_ClockConfig(&clk, FLASH_LATENCY_1);
}

void GPIO_Config(void)
{
    GPIO_InitTypeDef gpio = {0};
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /* PA0 = TIM1_CH1 (PWM out) */
    gpio.Pin       = PWM_PIN;
    gpio.Mode      = GPIO_MODE_AF_PP;
    gpio.Pull      = GPIO_NOPULL;
    gpio.Speed     = GPIO_SPEED_FREQ_HIGH;
    gpio.Alternate = GPIO_AF5_TIM1;
    HAL_GPIO_Init(PWM_PORT, &gpio);

    /* PA2 = USART2_TX, PA3 = USART2_RX */
    gpio.Pin       = UART_TX_PIN | UART_RX_PIN;
    gpio.Mode      = GPIO_MODE_AF_PP;
    gpio.Pull      = GPIO_PULLUP;
    gpio.Speed     = GPIO_SPEED_FREQ_HIGH;
    gpio.Alternate = UART_AF;
    HAL_GPIO_Init(UART_PORT, &gpio);
}

void TIM1_Config(void)
{
    TIM_ClockConfigTypeDef       clk = {0};
    TIM_MasterConfigTypeDef      mst = {0};
    TIM_OC_InitTypeDef           oc  = {0};
    TIM_BreakDeadTimeConfigTypeDef bd = {0};

    __HAL_RCC_TIM1_CLK_ENABLE();

    hpwm.Instance               = PWM_TIMER;
    hpwm.Init.Prescaler         = PWM_PRESCALER - 1U;
    hpwm.Init.CounterMode       = TIM_COUNTERMODE_UP;
    hpwm.Init.Period            = PWM_ARR;                  /* 2399 -> 20 kHz */
    hpwm.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
    hpwm.Init.RepetitionCounter = 0;
    hpwm.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    HAL_TIM_Base_Init(&hpwm);

    clk.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    HAL_TIM_ConfigClockSource(&hpwm, &clk);
    HAL_TIM_PWM_Init(&hpwm);

    mst.MasterOutputTrigger  = TIM_TRGO_RESET;
    mst.MasterOutputTrigger2 = TIM_TRGO2_RESET;
    mst.MasterSlaveMode      = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&hpwm, &mst);

    oc.OCMode      = TIM_OCMODE_PWM1;
    oc.Pulse       = VFD_DEFAULT_OFFSET; /* arrancar centrado */
    oc.OCPolarity  = TIM_OCPOLARITY_HIGH;
    oc.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    oc.OCFastMode  = TIM_OCFAST_DISABLE;
    oc.OCIdleState = TIM_OCIDLESTATE_RESET;
    oc.OCNIdleState= TIM_OCNIDLESTATE_RESET;
    HAL_TIM_PWM_ConfigChannel(&hpwm, &oc, TIM_CHANNEL_1);

    bd.OffStateRunMode  = TIM_OSSR_DISABLE;
    bd.OffStateIDLEMode = TIM_OSSI_DISABLE;
    bd.LockLevel        = TIM_LOCKLEVEL_OFF;
    bd.DeadTime         = 0;
    bd.BreakState       = TIM_BREAK_DISABLE;
    bd.BreakPolarity    = TIM_BREAKPOLARITY_HIGH;
    bd.BreakFilter      = 0;
    bd.BreakAFMode      = TIM_BREAK_AFMODE_INPUT;
    bd.Break2State      = TIM_BREAK2_DISABLE;
    bd.Break2Polarity   = TIM_BREAK2POLARITY_HIGH;
    bd.Break2Filter     = 0;
    bd.Break2AFMode     = TIM_BREAK_AFMODE_INPUT;
    bd.AutomaticOutput  = TIM_AUTOMATICOUTPUT_DISABLE;
    HAL_TIMEx_ConfigBreakDeadTime(&hpwm, &bd);

    /* URS=1 -> solo el overflow del contador genera UEV; UG por software no.
       Necesario porque HAL_TIM_PWM_Start() suele forzar UG y meter spurious IRQ. */
    PWM_TIMER->CR1 |= TIM_CR1_URS;
    __HAL_TIM_CLEAR_FLAG(&hpwm, TIM_FLAG_UPDATE);
    __HAL_TIM_ENABLE_IT  (&hpwm, TIM_IT_UPDATE);

    HAL_NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn, 0, 0);   /* maxima prioridad */
    HAL_NVIC_EnableIRQ  (TIM1_BRK_UP_TRG_COM_IRQn);
}

void USART2_Config(void)
{
    __HAL_RCC_USART2_CLK_ENABLE();

    hctrl.Instance        = CTRL_UART;
    hctrl.Init.BaudRate   = CTRL_UART_BAUD;
    hctrl.Init.WordLength = UART_WORDLENGTH_8B;
    hctrl.Init.StopBits   = UART_STOPBITS_1;
    hctrl.Init.Parity     = UART_PARITY_NONE;
    hctrl.Init.Mode       = UART_MODE_TX_RX;
    hctrl.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
    hctrl.Init.OverSampling = UART_OVERSAMPLING_16;
    hctrl.Init.OneBitSampling          = UART_ONE_BIT_SAMPLE_DISABLE;
    hctrl.Init.ClockPrescaler          = UART_PRESCALER_DIV1;
    hctrl.AdvancedInit.AdvFeatureInit  = UART_ADVFEATURE_NO_INIT;
    HAL_UART_Init(&hctrl);

    HAL_NVIC_SetPriority(USART2_IRQn, 2, 0); /* < TIM1 update */
    HAL_NVIC_EnableIRQ  (USART2_IRQn);

    HAL_UART_Receive_IT(&hctrl, (uint8_t *)&rx_byte, 1U);
}

uint8_t Hw_Init(void)
{
    HAL_Init();
    SystemClock_Config();
    GPIO_Config();
    TIM1_Config();
    USART2_Config();

    /* Defaults seguros: amp=0, offset centrado, fo=50 Hz.
       Asi arranca sin movimiento; el usuario fija amp por UART cuando quiere. */
    vfd_set_offset_ccr(VFD_DEFAULT_OFFSET);
    vfd_set_amplitude_q15(0);
    vfd_set_frequency_mhz(VFD_DEFAULT_FO_MHZ);

    HAL_TIM_PWM_Start(&hpwm, TIM_CHANNEL_1);
    return 1;
}

/* ===========================================================================
 *  ISRs
 * ========================================================================= */

/* TIM1 update -> DDS tick. ISR minima sin pasar por HAL para reducir jitter. */
void TIM1_BRK_UP_TRG_COM_IRQHandler(void)
{
    if (PWM_TIMER->SR & TIM_SR_UIF) {
        PWM_TIMER->SR = ~TIM_SR_UIF;
        vfd_update_ccr();
    }
}

/* USART2: dejo el grueso del trabajo a HAL_UART_IRQHandler; el callback
   HAL_UART_RxCpltCallback hace el acumulado del byte y rearma la recepcion. */
void USART2_IRQHandler(void)
{
    HAL_UART_IRQHandler(&hctrl);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart != &hctrl) return;
    uint8_t b = rx_byte;

    if (b == '\r' || b == '\n') {
        if (rx_idx > 0 && !rx_ready) {
            rx_line[rx_idx] = '\0';
            rx_ready = 1;                   /* el main lo procesa */
        }
    } else if (rx_idx < (CTRL_RX_BUF_LEN - 1U)) {
        rx_line[rx_idx++] = b;
    } else {
        /* overflow -> descartar linea */
        rx_idx = 0;
    }

    HAL_UART_Receive_IT(&hctrl, (uint8_t *)&rx_byte, 1U);
}

/* ===========================================================================
 *  Parser ASCII (ver CHANGES.md / vfd_protocol.md)
 *
 *  Formato:  <cmd><uint><CR|LF>
 *    F<mHz>     set frequency (milihertz, 0..VFD_FO_MAX_MHZ)
 *    A<q15>     set amplitude (0..32767)
 *    O<ccr>     set offset    (0..PWM_ARR)
 *    ?          query state
 *  Respuestas: "OK\r\n" / "ERR\r\n" / "F=.. A=.. O=..\r\n"
 * ========================================================================= */

static void uart_send(const char *s)
{
    HAL_UART_Transmit(&hctrl, (const uint8_t *)s, (uint16_t)strlen(s), HAL_MAX_DELAY);
}

/* atoi rapido y seguro para uint32 sin signo. Devuelve 0 si no hay digitos. */
static uint32_t parse_u32(const char *s, uint8_t *ok)
{
    uint32_t v = 0;
    *ok = 0;
    while (*s >= '0' && *s <= '9') {
        v = v * 10U + (uint32_t)(*s - '0');
        s++;
        *ok = 1;
    }
    return v;
}

static void process_line(const char *line)
{
    char     reply[48];
    uint8_t  ok;
    uint32_t val;

    switch (line[0]) {
    case '?':
        snprintf(reply, sizeof(reply), "F=%lu A=%u O=%u\r\n",
                 (unsigned long)vfd_get_frequency_mhz(),
                 (unsigned)     vfd_get_amplitude_q15(),
                 (unsigned)     vfd_get_offset_ccr());
        uart_send(reply);
        return;

    case 'F': case 'f':
        val = parse_u32(line + 1, &ok);
        if (!ok || val > VFD_FO_MAX_MHZ) break;
        vfd_set_frequency_mhz(val);
        uart_send("OK\r\n");
        return;

    case 'A': case 'a':
        val = parse_u32(line + 1, &ok);
        if (!ok || val > VFD_AMP_MAX_Q15) break;
        vfd_set_amplitude_q15((uint16_t)val);
        uart_send("OK\r\n");
        return;

    case 'O': case 'o':
        val = parse_u32(line + 1, &ok);
        if (!ok || val > PWM_ARR) break;
        vfd_set_offset_ccr((uint16_t)val);
        uart_send("OK\r\n");
        return;

    default:
        break;
    }
    uart_send("ERR\r\n");
}

void vfd_uart_poll(void)
{
    if (!rx_ready) return;
    /* copio fuera del buffer volatile para que process_line vea snapshot estable */
    char line[CTRL_RX_BUF_LEN];
    for (uint8_t i = 0; i < CTRL_RX_BUF_LEN; i++) line[i] = (char)rx_line[i];
    rx_idx   = 0;
    rx_ready = 0;
    process_line(line);
}
