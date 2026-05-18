/* Includes ---------*/
#include "main.h"

/* Global variables ----*/
extern uint8_t flag;

/* Main Function ----*/
int main(void)
{
  // Hardware Initialize
  Hw_Init();

  // Infinite Loop
  while (1)
  {
	  if(flag==1) HAL_GPIO_WritePin(LED_PORT, LED_PIN, LED_ON);
	  else HAL_GPIO_WritePin(LED_PORT, LED_PIN, LED_OFF);
  }

}
