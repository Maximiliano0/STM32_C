/* Includes ------------------------------*/
#include "my_lib.h"

/* Macros --------------------------------*/

/* Global Variable -----------------------*/
TIM_HandleTypeDef hbasetim; // TIM3 Handler Variable
TIM_HandleTypeDef hpwm; // TIM1 Handler Variable
volatile uint32_t sampling = 0;

/* Public Function Definitions ------------*/

/* Hardware Configuration */
uint8_t Hw_Init(void){

	/* HAL Initialization	*/
	HAL_Init(); // --> Init Software

	/* CLK Configuration */
	SystemClock_Config(); // --> Init Hardware

	/* TIM3 Configuration (Base Timer) */
	TIM3_Config();

	/* TIM1 Configuration (PWM Timer) */
	TIM1_Config();

	/* GPIO Configuration */
	GPIO_Config(); // --> Init Hardware

	return(1);
}


/* CLK Configuration */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /* A 48 MHz el flash de la STM32C0 necesita 1 wait state (datasheet: <=24 MHz = 0 WS,
     >24 MHz = 1 WS). Hay que ajustar la latencia ANTES de subir el reloj y luego
     volver a pasarla a HAL_RCC_ClockConfig. */
  __HAL_FLASH_SET_LATENCY(FLASH_LATENCY_1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;   // HSI 48 MHz sin dividir -> SYSCLK = 48 MHz
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;

  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);

}


/* GPIO Configuration */
void GPIO_Config(void){

	GPIO_InitTypeDef PWM_Pin_Conf = {0};

	/* GPIO Port Hardware Enable */
	// --> Hardware
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/* PWM Pin Features Load */
	// --> Software
	PWM_Pin_Conf.Pin = PWM_PIN;
	PWM_Pin_Conf.Mode = GPIO_MODE_AF_PP;
	PWM_Pin_Conf.Pull = GPIO_NOPULL;
	PWM_Pin_Conf.Speed = GPIO_SPEED_FREQ_LOW;
	PWM_Pin_Conf.Alternate = GPIO_AF5_TIM1;   

	/* PWM Pin Hardware Configuration */
	// --> Hardware
	HAL_GPIO_Init(PWM_PORT, &PWM_Pin_Conf);

	return;
}

/* TIM3 Configuration */
void TIM3_Config(void){

	TIM_ClockConfigTypeDef CLK_Source = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};

	/*  TIM Features Load */
	// --> Software
	hbasetim.Instance = BASE_TIMER;
	hbasetim.Init.Prescaler = BASE_PRESCALER-1;
	hbasetim.Init.CounterMode = TIM_COUNTERMODE_UP;
	/* Base tick = 100 us  ->  Ts = 100 us  ->  fs = 10 kHz (coincide con gen_signal.py).
	   Con _N = 200 muestras  ->  fo = 1 / (200 * 100 us) = 50 Hz.
	   1 IRQ por muestra: en el bucle principal solo se hace un load+store al CCR1
	   (la LUT ya viene pre-escalada por Python -> nada de float-math en runtime). */
	hbasetim.Init.Period = _BasePeriod(10);
	hbasetim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	hbasetim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	/* TIM Hardware Configuration */
	// --> Hardware
	HAL_TIM_Base_Init(&hbasetim);

	/* CLK Source Selection */
	CLK_Source.ClockSource = TIM_CLOCKSOURCE_INTERNAL; // --> Software
	HAL_TIM_ConfigClockSource(&hbasetim, &CLK_Source); // --> Hardware

	/* TIM OVF Interrupt Config */
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE; // --> Software
	HAL_TIMEx_MasterConfigSynchronization(&hbasetim, &sMasterConfig); // --> Hardware

	/* TIMER RUN (Interruption)	*/
	HAL_TIM_Base_Start_IT(&hbasetim); // --> Hardware

	return;
}

/* TIM1 Configuration (PWM carrier @ 1 MHz sobre PA0/TIM1_CH1) */
void TIM1_Config(void){

	  TIM_ClockConfigTypeDef CLK_Source = {0};
	  TIM_OC_InitTypeDef PWM_Config = {0};
	  TIM_MasterConfigTypeDef sMasterConfig = {0};
	  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};


	  /*  TIM Features Load */
	  // --> Software
	  hpwm.Instance = PWM_TIMER;
	  hpwm.Init.Prescaler = PWM_PRESCALER-1;
	  hpwm.Init.CounterMode = TIM_COUNTERMODE_UP;
	  hpwm.Init.Period = _PWMPeriod(Carrier_Period);
	  hpwm.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	  hpwm.Init.RepetitionCounter = 0;
	  hpwm.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

	  /* TIM Initialize */
	  HAL_TIM_Base_Init(&hpwm);

	  /* CLK Source Selection */
	  CLK_Source.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	  HAL_TIM_ConfigClockSource(&hpwm, &CLK_Source);

	  /* PWM Initialize */
	  HAL_TIM_PWM_Init(&hpwm);

	  /* Master/slave: TIM1 no se sincroniza con nadie (modo libre). */
	  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
	  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	  HAL_TIMEx_MasterConfigSynchronization(&hpwm, &sMasterConfig);

	  /* PWM Features Load */
	  // --> Software
	  PWM_Config.OCMode = TIM_OCMODE_PWM1;
	  PWM_Config.Pulse = 0;
	  PWM_Config.OCPolarity = TIM_OCPOLARITY_HIGH;
	  PWM_Config.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	  PWM_Config.OCFastMode = TIM_OCFAST_DISABLE;
	  PWM_Config.OCIdleState = TIM_OCIDLESTATE_RESET;
	  PWM_Config.OCNIdleState = TIM_OCNIDLESTATE_RESET;

	  /* PWM Hardware Configuration */
	  // --> Software
	  HAL_TIM_PWM_ConfigChannel(&hpwm, &PWM_Config, TIM_CHANNEL_1);

	  /*	Other TIM 1 Features Disable	*/
	  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
	  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
	  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
	  sBreakDeadTimeConfig.DeadTime = 0;
	  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
	  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
	  sBreakDeadTimeConfig.BreakFilter = 0;
	  sBreakDeadTimeConfig.BreakAFMode = TIM_BREAK_AFMODE_INPUT;
	  sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
	  sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
	  sBreakDeadTimeConfig.Break2Filter = 0;
	  sBreakDeadTimeConfig.Break2AFMode = TIM_BREAK_AFMODE_INPUT;
	  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
	  HAL_TIMEx_ConfigBreakDeadTime(&hpwm, &sBreakDeadTimeConfig);

	return;
}


/* TIM3 IRQ Definition */
void TIM3_IRQHandler(void)
{
  /* ISR ligera: solo limpia el flag de update y baja el contador de muestras.
     No se llama a HAL_TIM_IRQHandler() a proposito: ese wrapper hace varios
     reads/writes de registros y un switch grande -> en un Cortex-M0+ (sin
     branch predictor ni cache) se traduce en muchos ciclos por IRQ. Para
     fs=10 kHz preferimos esta ISR minima (~10 ciclos) y dejar el grueso del
     tiempo al main loop. */
  if (BASE_TIMER->SR & TIM_SR_UIF) {
    BASE_TIMER->SR = ~TIM_SR_UIF;
    if (sampling > 0) sampling--;
  }

  return;
}

/* Private Function Definitions ------------*/
