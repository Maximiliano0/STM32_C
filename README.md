# STM32_C

Material de cursos de **Microcontroladores** y **Lenguaje C** dictados por el **Ing. Maximiliano Vega**.

Reúne ejercicios de C bare metal, proyectos STM32 (HAL, CubeIDE) sobre dos plataformas (Nucleo-F401RE y Nucleo-C031C6) y prototipos en Python de algoritmos de DSP que luego se implementan en el microcontrolador.

---

## Cursos

| Curso                                | Universidad | Plataforma            |
|--------------------------------------|-------------|-----------------------|
| Microprocesadores y Control (22.57)  | ITBA        | STM32 Nucleo-F401RE   |
| Microcontroladores II                | UCA         | STM32 Nucleo-C031C6   |

---

## Estructura del repositorio

```
STM32_C/
├── Lenguaje_C/         Fundamentos y prácticas en C estándar
│   ├── ITBA-Micros-I/  Clases ITBA + TPN1 (10 ejercicios)
│   └── UCA-Micros-II/  Máquinas de estado (switch-case y table-driven)
│
├── STM32F401RE/        Proyectos STM32CubeIDE para Nucleo-F401RE (ITBA)
│
├── STM32C031C6/        Proyectos STM32CubeIDE para Nucleo-C031C6 (UCA)
│
├── DSP/                Prototipos Python de algoritmos DSP
│   ├── Convolution/    Convolución (zero-pad, buffer limitado)
│   ├── FIR_IIR/        Filtros FIR e IIR
│   └── Windowing/      Ventanas (Hamming, Hanning, Blackman, etc.)
│
├── Comunicación Serie.pptx
└── Maquinas de Estado.pptx
```

Las carpetas con prefijo `AAAAMMDD-` indican la fecha de clase, lo que permite seguir el dictado en orden cronológico.

---

## Lenguaje C — temas cubiertos

- Programa mínimo, E/S por consola (`hola`, `parity`, `upper`)
- Bibliotecas auxiliares, captura de teclado, `my_printf` casero
- Recursión vs iteración (`fibo`, convoluciones recursivas y no recursivas)
- Strings, ordenamiento (`bubble_sort`), buffers circulares
- Punteros, aritmética de punteros, punteros a función, arrays de punteros
- Manejo de archivos
- Modularización: librerías (`my_lib`, `lib1`, `lib2`)
- Tabla de saltos / punteros virtuales (`vpointer`)
- Máquinas de estado: `switch-case` vs `table-driven`
- **TPN1**: 10 ejercicios integradores (`Lenguaje_C/ITBA-Micros-I/TPN1`)

---

## STM32F401RE (ITBA) — proyectos

Generados con **STM32CubeMX / STM32CubeIDE**, HAL de ST. Board: **Nucleo-F401RE** (Cortex-M4F @ 84 MHz).

| Fecha     | Proyecto              | Tema                                         |
|-----------|-----------------------|----------------------------------------------|
| 20260415  | `button_led`          | GPIO básico: lectura de pulsador y LED       |
| 20260420  | `Blinky_CleanCode`    | Blinky aplicando *clean code*                |
| 20260420  | `Button_PWM`          | PWM controlado por pulsador                  |
| 20260422  | `DeBounce`            | Antirrebote por software                     |
| 20260427  | `ADC_Test`            | Lectura analógica con ADC                    |
| 20260427  | `FIR`                 | Filtro FIR sobre muestras del ADC            |
| 20260502  | `button_clicks`       | Detección de clicks simples / dobles / largos|
| 20260506  | `USART_Polling`       | UART por polling                             |
| 20260506  | `USART_RxIT`          | UART por interrupción (RX-IT)                |

---

## STM32C031C6 (UCA) — proyectos

Generados con **STM32CubeMX / STM32CubeIDE**, HAL de ST. Board: **Nucleo-C031C6** (Cortex-M0+ @ 48 MHz).

| Fecha     | Proyecto              | Tema                                                      |
|-----------|-----------------------|-----------------------------------------------------------|
| 20260409  | `first_program`       | Primer proyecto: setup, clocks, GPIO                      |
| 20260423  | `tim_pwm_project`     | Generación de PWM con TIMx                                |
| 20260429  | `tim_debounce`        | Antirrebote por timer                                     |
| 20260507  | `UART_Polling`        | UART por polling                                          |
| 20260514  | `analog_pwm`          | DAC sintetizado por PWM + filtro RC (`gen_signal.py`)     |
| 20260520  | `vfd_pwm`             | Control de Variable Frequency Drive por PWM (`vfd_helper.py`) |

Las carpetas que incluyen scripts `.py` contienen utilidades de generación / análisis de señales para acompañar el proyecto en C.

---

## DSP (Python)

Prototipos numéricos en Python que sirven como referencia para luego implementar los algoritmos en el microcontrolador.

- **Convolution/** — convolución discreta paso a paso, `zero_pad`, `limited_buffer`, comparación con `numpy.convolve`.
- **FIR_IIR/** — diseño y simulación de filtros FIR e IIR.
- **Windowing/** — ventanas de Hamming, Hanning, Blackman, Bartlett y rectangular aplicadas a señales de prueba.

Requisitos típicos: `numpy`, `matplotlib`, `scipy`.

---

## Cómo abrir los proyectos STM32

1. Instalar [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html).
2. `File → Open Projects from File System…` y seleccionar la carpeta del proyecto deseado dentro de `STM32F401RE/` o `STM32C031C6/`.
3. Build (`Ctrl+B`) y flash sobre la placa Nucleo correspondiente.

> Los proyectos incluyen las carpetas `Drivers/`, `Debug/` y `.settings/` para que estén listos para abrir y compilar sin tener que regenerar desde el `.ioc`.

---

## Material de soporte

- `Comunicación Serie.pptx` — fundamentos de UART/USART y ejemplos.
- `Maquinas de Estado.pptx` — `switch-case` vs *table-driven*.

---

## Autor

**Ing. Maximiliano Vega**  
Docente de Microcontroladores — ITBA · UCA  
GitHub: [@Maximiliano0](https://github.com/Maximiliano0)
