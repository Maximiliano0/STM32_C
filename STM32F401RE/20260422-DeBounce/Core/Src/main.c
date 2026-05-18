/* Includes ---------*/
#include "main.h"

/* Global variables ----*/
extern volatile uint8_t counter;

/* Main Function ----*/
int main(void)
{
  // Hardware Initialize
  Hw_Init();

  // Infinite Loop
  while (1)
  {
	  /* Change LED state when Button is Pressed */
	  if(SWITCH_Filtered(SWITCH_PORT, SWITCH_PIN)==Pressed) HAL_GPIO_WritePin(LED_PORT, LED_PIN, LED_ON);
	  else HAL_GPIO_WritePin(LED_PORT, LED_PIN, LED_OFF);
  }
}


