/* Includes ------------------------------*/
#include "my_lib.h"

/* Macros --------------------------------*/

/* Global Variable -----------------------*/
TIM_HandleTypeDef hledtim; // TIM2 Handler Variable --> Software
volatile uint8_t counter = 0;

/* Public Function Definitions ------------*/

/* Hardware Configuration */
uint8_t Hw_Init(void){

	/* HAL Initialization	*/
	HAL_Init(); // --> Init Software

	/* CLK Configuration */
	SystemClock_Config(); // --> Init Hardware

	/* GPIO Configuration */
	GPIO_Config(); // --> Init Hardware

	/* TIM2 Configuration */
	TIM2_Config(); // --> Init Hardware


	return(1);
}


/* CLK Configuration */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0);

  return;
}

/* GPIO Configuration */
void GPIO_Config(void){

	GPIO_InitTypeDef LED_Pin_Conf = {0};
	GPIO_InitTypeDef SWITCH_Pin_Conf = {0};

	/* GPIO Port Hardware Enable */
	// --> Hardware
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/* LED Initial State : OFF */
	HAL_GPIO_WritePin(LED_PORT, LED_PIN, LED_OFF);

	/* LED Pin Features Load */
	// --> Software
	LED_Pin_Conf.Pin = LED_PIN;
	LED_Pin_Conf.Mode = GPIO_MODE_OUTPUT_PP;
	LED_Pin_Conf.Pull = GPIO_NOPULL;
	LED_Pin_Conf.Speed = GPIO_SPEED_FREQ_LOW;

	/* LED Pin Hardware Configuration */
	// --> Hardware
	HAL_GPIO_Init(LED_PORT, &LED_Pin_Conf);

	/* SWITCH Pin Features Load */
	// --> Software
	SWITCH_Pin_Conf.Pin = SWITCH_PIN;
	SWITCH_Pin_Conf.Mode = GPIO_MODE_INPUT;
	SWITCH_Pin_Conf.Pull = GPIO_NOPULL;
	SWITCH_Pin_Conf.Speed = GPIO_SPEED_FREQ_LOW;

	/* SWITCH Pin Hardware Configuration */
	// --> Hardware
	HAL_GPIO_Init(SWITCH_PORT, &SWITCH_Pin_Conf);


	return;
}

/* TIM2 Configuration */
void TIM2_Config(void){

	TIM_ClockConfigTypeDef CLK_Source = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};

	/*  TIM Features Load */
	// --> Software
	hledtim.Instance = BASE_TIMER;
	hledtim.Init.Prescaler = BASE_PRESCALER-1;
	hledtim.Init.CounterMode = TIM_COUNTERMODE_UP;
	hledtim.Init.Period = _BasePeriod(1); // 1 [ms]
	hledtim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	hledtim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	/* TIM Hardware Configuration */
	// --> Hardware
	HAL_TIM_Base_Init(&hledtim);

	/* CLK Source Selection */
	CLK_Source.ClockSource = TIM_CLOCKSOURCE_INTERNAL; // --> Software
	HAL_TIM_ConfigClockSource(&hledtim, &CLK_Source); // --> Hardware

	/* TIM OVF Interrupt Config */
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE; // --> Software
	HAL_TIMEx_MasterConfigSynchronization(&hledtim, &sMasterConfig); // --> Hardware

	/* TIMER RUN (Interruption)	*/
	HAL_TIM_Base_Start_IT(&hledtim); // --> Hardware

	return;
}

/* Filtered Read Pin */
Button_State  SWITCH_Filtered(GPIO_TypeDef* GPIO_PORT, uint16_t GPIO_PIN){

    static Button_State stable_state    = Non_Pressed;
    static Button_State last_state = Non_Pressed;
    Button_State actual_state;

	/* Read Pin */
	actual_state = (HAL_GPIO_ReadPin(GPIO_PORT, GPIO_PIN)==SWITCH_ON)?	Pressed:Non_Pressed;

	/* Check if There is a State Change */
	if(actual_state != last_state){
		/* Save previous state */
		last_state = actual_state;
		/* Delay Start */
		counter = DeBounce_Delay;
	}
	else{
		/* Delay Ended */
		if((counter==0) && (last_state != stable_state)){
			/* If its maintain equal after DeBounce_Delay */
			stable_state = last_state;
		}
	}

	return(stable_state);
}


/* TIM2 IRQ Definition */
void TIM2_IRQHandler(void)
{

  /* TIM2 IT CATCH */
  HAL_TIM_IRQHandler(&hledtim); // --> Hardware

  /* COUNT */
  if(counter > 0) counter--;

  return;
}



/* Private Function Definitions ------------*/
