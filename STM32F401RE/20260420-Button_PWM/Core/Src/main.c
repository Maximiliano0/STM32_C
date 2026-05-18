/* Includes ---------*/
#include "main.h"

/* Global variables ----*/
extern uint8_t sampling, delay;
extern TIM_HandleTypeDef hpwm;

/* Main Function ----*/
int main(void)
{
  int dutty = 30;
  // Hardware Initialize
  Hw_Init();

  // Sampling Tick
  sampling = Sampling_Period;

  // PWM Start
  HAL_TIM_PWM_Start(&hpwm, TIM_CHANNEL_1);

  // Infinite Loop
  while (1)
  {
	  /* Change LED state when Button is Pressed */
	  if(CLICK_Detect(SWITCH_PORT, SWITCH_PIN) == Clicked){
		  if(dutty < 100) dutty += 10;
		  else dutty = 0;
		  TIM2->CCR1 = _PWMDutty(dutty, _PWMPeriod(100));
	  }

  }
}


