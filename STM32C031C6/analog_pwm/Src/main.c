/* Includes ---------*/
#include "main.h"

/* Numero de muestras por periodo de la senal: lo provee signal_array.c
   (auto-generado por gen_signal.py, junto con la LUT `ccr_table[]`).
   _N es dinamico: lo dicta la LUT. Valor actual: ccr_len = 200, Ts = 100 us
   ->  fo = 1 / (200 * 100 us) = 50 Hz. Si regeneras con otra N o fo desde
   Python, este firmware se adapta sin recompilar nada mas. */
#define _N  (ccr_len)

/* Global variables ----*/
extern TIM_HandleTypeDef hpwm;       // definido en my_lib.c
extern volatile uint32_t sampling;   // definido en my_lib.c, decrementado en la ISR de TIM3

/* `ccr_table[]` y `ccr_len` se declaran en my_lib.h y se definen en signal_array.c
   (generado por gen_signal.py, ya pre-escalados al ARR del PWM). */


/* Main Function ----*/
int main(void)
{
  uint32_t i = 0;

  /* Hardware Initialize */
  Hw_Init();

  /* Arranque del tick de muestreo: TIM3 desborda cada 100 us (Ts).
     Con Sampling_Period = 1, una IRQ de TIM3 = una muestra nueva.
     fo = 1 / (_N * Ts)  ->  con _N=200, Ts=100us  ->  fo = 50 Hz.   */
  sampling = Sampling_Period;

  /* PWM Start */
  HAL_TIM_PWM_Start(&hpwm, TIM_CHANNEL_1);

  /* Infinite Loop */
  while (1)
  {
    if (sampling == 0) {
      /* 1) Volcar la muestra ya pre-escalada al CCR1 (TIM1_CH1 -> PA0).
            Sin floats, sin multiplicaciones: solo un load + store.        */
      PWM_TIMER->CCR1 = ccr_table[i];

      /* 2) Avanzar indice con wrap (no leer fuera del array). */
      i++;
      if (i >= _N) i = 0;

      /* 3) Rearmar el tick: la proxima IRQ de TIM3 dispara la siguiente muestra. */
      sampling = Sampling_Period;
    }
  }
}
