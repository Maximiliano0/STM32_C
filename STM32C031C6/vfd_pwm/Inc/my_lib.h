/* Includes ------------------------------*/
#include "stm32c0xx_hal.h"

/* ============================================================================
 *  vfd_pwm  --  Variador de frecuencia directa monofasico
 *
 *  Arquitectura:
 *   - TIM1_CH1 -> PA0 : portadora PWM @ 20 kHz (ARR=2399, 11.2 bits de duty).
 *   - TIM1 Update IRQ : una IRQ por periodo de portadora (fs = 20 kHz).
 *                       En la IRQ se ejecuta el DDS (vfd_update_ccr) que
 *                       calcula el nuevo CCR1 a partir de la LUT Q15 +
 *                       offset/amp/frec actuales.
 *   - USART2 (PA2 TX / PA3 RX, 115200 8N1, IRQ RX) : interfaz de control.
 *   - TIM3   : ELIMINADO.
 *
 *  La LUT (sine_q15[256]) es normalizada y NUNCA se regenera para nuevos
 *  puntos de operacion: la frecuencia se controla por phase_inc del DDS,
 *  la amplitud por una multiplicacion Q15, y el offset por una suma.
 * ========================================================================== */

/* ---- Reloj y portador ----------------------------------------------------- */
#define CORE_CLK            48000000UL     /* SYSCLK = HSI/1 = 48 MHz, FLASH WS=1 */
#define CARRIER_PERIOD_US   50U            /* 50 us  ->  20 kHz portadora */

#define PWM_PORT            GPIOA
#define PWM_PIN             GPIO_PIN_0
#define PWM_TIMER           TIM1
#define PWM_PRESCALER       1U
#define _PWMPeriod(x_us)    (((x_us) * (CORE_CLK/1000000UL) / PWM_PRESCALER) - 1U)
#define PWM_ARR             _PWMPeriod(CARRIER_PERIOD_US)   /* 2399 */
#define PWM_PERIOD_COUNTS   (PWM_ARR + 1U)                  /* 2400 */

/* fs del DDS = frecuencia de la portadora (una muestra por periodo PWM). */
#define FS_HZ               (CORE_CLK / PWM_PERIOD_COUNTS)  /* 20000 */

/* ---- UART de control ------------------------------------------------------ */
#define UART_PORT           GPIOA
#define UART_TX_PIN         GPIO_PIN_2
#define UART_RX_PIN         GPIO_PIN_3
#define UART_AF             GPIO_AF1_USART2
#define CTRL_UART           USART2
#define CTRL_UART_BAUD      115200U
#define CTRL_RX_BUF_LEN     32U            /* longitud maxima de comando ASCII */

/* ---- DDS (LUT Q15) -------------------------------------------------------- */
#define WAVE_LUT_BITS       8U
#define WAVE_LUT_SIZE       (1U << WAVE_LUT_BITS)           /* 256 */
extern const int16_t sine_q15[WAVE_LUT_SIZE];

/* ---- Limites V/f y defaults ----------------------------------------------- */
#define VFD_AMP_MAX_Q15     32767U
#define VFD_OFFSET_CENTER   (PWM_PERIOD_COUNTS / 2U)         /* 1200 */
#define VFD_DEFAULT_FO_MHZ  50000UL                          /* 50.000 Hz */
#define VFD_DEFAULT_AMP     ((uint16_t)((VFD_AMP_MAX_Q15 * 80U) / 100U))  /* 80% */
#define VFD_DEFAULT_OFFSET  ((uint16_t)VFD_OFFSET_CENTER)
#define VFD_FO_MAX_MHZ      ((FS_HZ * 1000UL) / 2UL)         /* Nyquist */

/* ---- Handles globales ----------------------------------------------------- */
extern TIM_HandleTypeDef  hpwm;
extern UART_HandleTypeDef hctrl;

/* ============================================================================
 *  API publica
 * ========================================================================== */

/* Inicializacion completa (clock, GPIO, TIM1, USART2, NVIC). */
uint8_t Hw_Init(void);

/* Setters crudos (atomicos: phase_inc/amp_q15/offset_ccr son volatile uint32). */
void vfd_set_frequency_mhz(uint32_t fo_mHz);   /* fo en milihertz */
void vfd_set_amplitude_q15(uint16_t amp_q15);  /* 0..32767 */
void vfd_set_offset_ccr   (uint16_t off_ccr);  /* 0..PWM_ARR  */

/* Getters (para responder al comando '?' por UART). */
uint32_t vfd_get_frequency_mhz(void);
uint16_t vfd_get_amplitude_q15(void);
uint16_t vfd_get_offset_ccr   (void);

/* Loop de servicio del parser UART: llamar desde el while(1) del main. */
void vfd_uart_poll(void);

/* ---- Prototipos internos (declarados para que el linker los vea) ---------- */
void SystemClock_Config(void);
void GPIO_Config(void);
void TIM1_Config(void);
void USART2_Config(void);

void TIM1_BRK_UP_TRG_COM_IRQHandler(void);
void USART2_IRQHandler(void);
