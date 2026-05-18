/* Punto de entrada del proyecto: solo arrastra los includes que main.c necesita.
   Toda la configuracion HW y los simbolos publicos del proyecto viven en my_lib.h. */

/* Includes --------------------------*/
#include "stm32c0xx_hal.h"
#include "my_lib.h"

/* Exported functions prototypes -----*/
void Error_Handler(void);
