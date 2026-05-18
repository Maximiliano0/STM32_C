/* Includes ------------------------------*/
#include "stm32f4xx_hal.h"

/* Macros --------------------------------*/
#define PWM_PORT  GPIOA
#define PWM_PIN   GPIO_PIN_0

#define LED_PORT  GPIOA
#define LED_PIN   GPIO_PIN_9
#define LED_OFF   GPIO_PIN_RESET
#define LED_ON    GPIO_PIN_SET

#define SWITCH_PORT  GPIOC
#define SWITCH_PIN   GPIO_PIN_13
#define SWITCH_OFF   GPIO_PIN_SET
#define SWITCH_ON    GPIO_PIN_RESET
#define DeBounce_Delay	20 // 20 [ms]

#define BASE_TIMER TIM3
#define BASE_PRESCALER 1000
#define _BasePeriod(x)	(((x * (CORE_CLK/1000)) / BASE_PRESCALER)-1)  // Period in [ms] non fractional

#define PWM_TIMER TIM2
#define PWM_PRESCALER 1000
#define _PWMPeriod(x)	(((x * (CORE_CLK/1000)) / PWM_PRESCALER)-1)  // Period in [ms] non fractional

#define _PWMDutty(x,y)	((uint32_t) ((((float) x)/100) * y))  // Dutty in percentage

#define CORE_CLK  16000000 // 16 MHz
#define Sampling_Period 10 // 10 [ms]

/* Variable Types ------------------------*/
typedef enum{
	Pressed = SWITCH_ON,
	Non_Pressed = SWITCH_OFF
}Button_State;

typedef enum{
	Clicked = 1,
	Non_Clicked = 0
}Click_State;

typedef enum{
	BTN_USER = 0,
	// BTN_NEXT,
	// BTN_PREV,
	BTN_COUNT // Array Size
}Button_Id;

typedef struct{
	GPIO_TypeDef *port; // GPIO Port
	uint16_t      pin;  // GPIO Pin
	uint8_t       state; // FSM State
}Button_t;


/* Public Function Prototypes ------------*/
uint8_t Hw_Init(void); // Hardware Configuration
void SystemClock_Config(void); // CLK Configuration
void GPIO_Config(void); // GPIO Configuration
void TIM3_Config(void); // TIM3 Configuration
void TIM2_Config(void); // TIM2 Configuration
void TIM3_IRQHandler(void); // TIM3 IRQ Routine
Click_State CLICK_Detect(Button_Id id);

/* Private Function Prototypes ------------*/
