/* Includes -----------*/
#include "main.h"

/* ============================================================================
 *  vfd_pwm  --  main
 *
 *  Toda la "accion" del firmware ocurre en interrupciones:
 *   - TIM1 update IRQ (cada 50 us)  : DDS -> nuevo CCR1.
 *   - USART2 RX IRQ   (por byte)    : acumulado de comando ASCII.
 *
 *  El bucle principal solo despacha lineas recibidas por UART (parser).
 *  Sin floats. Sin polling de tiempo. La salida arranca con amp=0
 *  (sin movimiento) hasta que el usuario fije amplitud via UART.
 * ========================================================================== */
int main(void)
{
    Hw_Init();
    while (1) {
        vfd_uart_poll();
    }
}

/* Para compatibilidad con main.h (declarado pero el firmware no lo usa). */
void Error_Handler(void)
{
    __disable_irq();
    while (1) { }
}
