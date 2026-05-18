
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32c0xx_it.h"

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim3;
extern volatile uint8_t debounce;

/******************************************************************************/
/*           Cortex Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
   while (1)
  {
  }
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  while (1)
  {
	  // Aviso ej: Display pongo Error de Memoria
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  HAL_IncTick();
}


/**
  * @brief This function handles TIM3 global interrupt.
  */
void TIM3_IRQHandler(void)
{

  // Contador de Tiempo
  if(debounce > 0) debounce--;

  HAL_TIM_IRQHandler(&htim3);

}

