/* Includes ---------*/
#include "main.h"

#define _N 10000

/* Global variables ----*/
extern uint32_t sampling, delay;
extern TIM_HandleTypeDef hpwm;
extern ADC_HandleTypeDef hadc;

/* Main Function ----*/
int main(void)
{
  uint32_t counts = 0;
  float voltage = 0;

  // Hardware Initialize
  Hw_Init();

  // Sampling Tick
  sampling = Sampling_Period;

  // PWM Start
  HAL_TIM_PWM_Start(&hpwm, TIM_CHANNEL_1);

  // Infinite Loop
  while (1)
  {
	  if(sampling==0){
		  // ADC Start
		  HAL_ADC_Start(&hadc);
		  // Poll for 100us
		  HAL_ADC_PollForConversion(&hadc, 100);
		  // Read Value
		  counts = HAL_ADC_GetValue(&hadc);
		  // ADC Stop
		  HAL_ADC_Stop(&hadc);

		  voltage = counts * (ADC_RES);
	  }
  }
}


