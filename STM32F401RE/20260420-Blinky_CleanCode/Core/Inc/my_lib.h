/* Includes ------------------------------*/
#include "stm32f4xx_hal.h"

/* Macros --------------------------------*/
#define LED_PORT  GPIOA
#define LED_PIN   GPIO_PIN_9
#define LED_OFF   GPIO_PIN_RESET
#define LED_ON    GPIO_PIN_SET

#define LED_TIMER TIM2
#define CORE_CLK  16000000 // 16 MHz
#define LED_PRESCALER 1000
#define _LedPeriod(x)	(((x * (CORE_CLK/1000)) / LED_PRESCALER)-1)  // Period in [ms] non fractional


/* Variable Types ------------------------*/

/* Public Function Prototypes ------------*/
uint8_t Hw_Init(void); // Hardware Configuration
void SystemClock_Config(void); // CLK Configuration
void GPIO_Config(void); // GPIO Configuration
void TIM2_Config(void); // TIM2 Configuration
void TIM2_IRQHandler(void); // TIM2 IRQ Routine

/* Private Function Prototypes ------------*/
