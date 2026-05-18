/* Includes ------------------------------*/
#include "stm32c0xx_hal.h"

/* Macros --------------------------------*/
#define PWM_PORT  GPIOA
#define PWM_PIN   GPIO_PIN_0

/* ---- Base timer (TIM3): genera 1 IRQ por muestra ---------------------------
 * `_BasePeriod(x)` calcula el ARR para que el timer desborde cada x * 10 us.
 * Con `_BasePeriod(10)` (ver TIM3_Config) -> Ts = 100 us -> fs = 10 kHz
 * (mismo fs que usa gen_signal.py al construir la tabla `ccr_table[]`).
 * -------------------------------------------------------------------------- */
#define BASE_TIMER TIM3
#define BASE_PRESCALER 1
#define _BasePeriod(x)	(((x * (CORE_CLK/100000)) / BASE_PRESCALER)-1)  // x en unidades de 10 us

/* ---- PWM carrier (TIM1_CH1 -> PA0) -----------------------------------------
 * `_PWMPeriod(x)` calcula el ARR para un periodo de PWM de x * 1 us.
 * Con `Carrier_Period = 1` y SYSCLK=48 MHz -> ARR = 47 -> 48 niveles de duty
 * (paso de ~2.08%). El filtro pasa-bajos externo recupera el seno.
 * IMPORTANTE: cualquier cambio aqui obliga a regenerar la tabla con
 * gen_signal.py (Python necesita el mismo CORE_CLK y Carrier_Period para
 * pre-escalar correctamente los valores de CCR1).
 * -------------------------------------------------------------------------- */
#define PWM_TIMER TIM1
#define PWM_PRESCALER 1
#define _PWMPeriod(x)	(((x * (CORE_CLK/1000000)) / PWM_PRESCALER)-1)  // x en unidades de 1 us
#define Carrier_Period ((uint32_t) 1) // 1 us  ->  carrier = 1 MHz

#define CORE_CLK  48000000 // SYSCLK = HSI(48 MHz) / HSIDIV(1) = 48 MHz (requiere 1 wait state de flash)

/* Cuantas IRQs de TIM3 forman 1 muestra. Con TIM3 ya configurado a 100 us,
   basta 1 IRQ por muestra para obtener Ts = 100 us. */
#define Sampling_Period ((uint32_t) 1)

/* Variable Types ------------------------*/

/* Tabla de CCR1 PRE-ESCALADA por gen_signal.py para el ARR actual del PWM
   (= _PWMPeriod(Carrier_Period)+1 = 48 cuentas). El firmware solo hace
   `TIM1->CCR1 = ccr_table[i]` -> sin floats, sin cuentas en runtime.
   Vive en signal_array.c (auto-generado). */
extern const uint16_t ccr_table[];
extern const uint32_t ccr_len;

/* Public Function Prototypes ------------*/
uint8_t Hw_Init(void); // Hardware Configuration
void SystemClock_Config(void); // CLK Configuration
void GPIO_Config(void); // GPIO Configuration
void TIM3_Config(void); // TIM3 Configuration (base timer, 100 us)
void TIM1_Config(void); // TIM1 Configuration (PWM carrier, 1 us)
void TIM3_IRQHandler(void); // TIM3 IRQ Routine

/* Private Function Prototypes ------------*/
