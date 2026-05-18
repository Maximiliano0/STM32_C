# STM32_C

Material de cursos de **Microcontroladores** y **Lenguaje C** dictados por el **Ing. Maximiliano Vega**.

Reúne ejercicios de C bare metal, proyectos STM32 (HAL, CubeIDE) sobre dos plataformas (Nucleo-F401RE y Nucleo-C031C6) y prototipos en Python de algoritmos de DSP que luego se implementan en el microcontrolador.

---

## Plataformas

| Curso                   | Plataforma            | Núcleo                       |
|-------------------------|-----------------------|------------------------------|
| Microcontroladores I    | STM32 Nucleo-F401RE   | Cortex-M4F @ 84 MHz          |
| Microcontroladores II   | STM32 Nucleo-C031C6   | Cortex-M0+  @ 48 MHz         |

---

## Estructura del repositorio

```text
STM32_C/
├── Lenguaje_C/                Fundamentos y prácticas en C estándar
│   ├── Ejercitación/          Clases + TPN1 (10 ejercicios)
│   │   ├── 01_hello_io/
│   │   ├── 02_libs_printf/
│   │   ├── 03_recursion_strings/
│   │   ├── 04_sorting_buffer/
│   │   ├── 05_pointers_files/
│   │   ├── 06_modular_libs/
│   │   ├── 07_multi_lib/
│   │   ├── 08_vpointer/
│   │   ├── 09_state_machines/
│   │   └── TPN1/
│   └── Maquinas de Estado/
│       └── state_machines/    switch-case vs table-driven
│
├── STM32F401RE/               Proyectos CubeIDE para Nucleo-F401RE
│   ├── button_led/
│   ├── Blinky_CleanCode/
│   ├── Button_PWM/
│   ├── DeBounce/
│   ├── ADC_Test/
│   ├── FIR/
│   ├── button_clicks/
│   ├── USART_Polling/
│   └── USART_RxIT/
│
├── STM32C031C6/               Proyectos CubeIDE para Nucleo-C031C6
│   ├── first_program/
│   ├── tim_pwm_project/
│   ├── tim_debounce/
│   ├── UART_Polling/
│   ├── analog_pwm/            DAC sintetizado por PWM (incluye gen_signal.py)
│   └── vfd_pwm/               Control de VFD por PWM (incluye vfd_helper.py)
│
├── DSP/                       Prototipos Python de algoritmos DSP
│   ├── Convolution/           zero_pad, buffer limitado, my_convolution
│   ├── FIR_IIR/               Filtros FIR e IIR
│   └── Windowing/             Hamming, Hanning, Blackman, Bartlett, …
│
├── extra/                     Presentaciones de soporte
│   ├── Comunicación Serie.pptx
│   └── Maquinas de Estado.pptx
│
└── README.md
```

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
- **TPN1**: 10 ejercicios integradores (`Lenguaje_C/Ejercitación/TPN1`)

---

## STM32F401RE — proyectos

Generados con **STM32CubeMX / STM32CubeIDE**, HAL de ST. Board: **Nucleo-F401RE** (Cortex-M4F @ 84 MHz).

| Proyecto              | Tema                                            |
|-----------------------|-------------------------------------------------|
| `button_led`          | GPIO básico: lectura de pulsador y LED          |
| `Blinky_CleanCode`    | Blinky aplicando *clean code*                   |
| `Button_PWM`          | PWM controlado por pulsador                     |
| `DeBounce`            | Antirrebote por software                        |
| `ADC_Test`            | Lectura analógica con ADC                       |
| `FIR`                 | Filtro FIR sobre muestras del ADC               |
| `button_clicks`       | Detección de clicks simples / dobles / largos   |
| `USART_Polling`       | UART por polling                                |
| `USART_RxIT`          | UART por interrupción (RX-IT)                   |

---

## STM32C031C6 — proyectos

Generados con **STM32CubeMX / STM32CubeIDE**, HAL de ST. Board: **Nucleo-C031C6** (Cortex-M0+ @ 48 MHz).

| Proyecto              | Tema                                                          |
|-----------------------|---------------------------------------------------------------|
| `first_program`       | Primer proyecto: setup, clocks, GPIO                          |
| `tim_pwm_project`     | Generación de PWM con TIMx                                    |
| `tim_debounce`        | Antirrebote por timer                                         |
| `UART_Polling`        | UART por polling                                              |
| `analog_pwm`          | DAC sintetizado por PWM + filtro RC (`gen_signal.py`)         |
| `vfd_pwm`             | Control de Variable Frequency Drive por PWM (`vfd_helper.py`) |

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

## Material de soporte (`extra/`)

- `Comunicación Serie.pptx` — fundamentos de UART/USART y ejemplos.
- `Maquinas de Estado.pptx` — `switch-case` vs *table-driven*.

---

## Autor

**Ing. Maximiliano Vega**
Docente de Microcontroladores
GitHub: [@Maximiliano0](https://github.com/Maximiliano0)
