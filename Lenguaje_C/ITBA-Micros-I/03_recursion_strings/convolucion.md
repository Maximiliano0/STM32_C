# Convolucion discreta en C
## Ejemplo con 64 muestras de entrada y moving average

> Documento actualizado para `non_recursive_conv.c` y `recursive_conv.c`.

---

## 1) Modelo matematico

La convolucion discreta entre una entrada `x[n]` y un filtro FIR `h[k]`:

$$
y[n] = \sum_{k=0}^{K-1} x[n-k] \, h[k]
$$

Con zero-padding en bordes:

$$
x[m] = 0, \quad m < 0 \;\text{o}\; m \ge N
$$

Longitud de salida:

$$
N_y = N + K - 1
$$

Para el promedio movil cuadrado de 4 muestras:

$$
h[k] = [1,1,1,1], \qquad G = \sum h[k] = 4, \qquad y_N[n] = \frac{y[n]}{4}
$$

---

## 2) Datos del ejemplo (actualizados)

El ejemplo aumenta la tasa de muestreo: pasa de 16 a 64 muestras de entrada
mediante sobremuestreo x4 por retencion (cada muestra se repite 4 veces).

| Senal | Valores |
|---|---|
| `x[n]` | `[4,4,4,4,6,6,6,6,8,8,8,8,7,7,7,7,6,6,6,6,4,4,4,4,2,2,2,2,1,1,1,1,0,0,0,0,1,1,1,1,2,2,2,2,4,4,4,4,6,6,6,6,7,7,7,7,8,8,8,8,7,7,7,7]` |
| `h[k]` | `[1, 1, 1, 1]` |
| `y[n]` | `[4,8,12,16,18,20,22,24,26,28,30,32,31,30,29,28,27,26,25,24,22,20,18,16,14,12,10,8,7,6,5,4,3,2,1,0,1,2,3,4,5,6,7,8,10,12,14,16,18,20,22,24,25,26,27,28,29,30,31,32,31,30,29,28,21,14,7]` |
| `y_N[n]` | `[1.00,2.00,3.00,4.00,4.50,5.00,5.50,6.00,6.50,7.00,7.50,8.00,7.75,7.50,7.25,7.00,6.75,6.50,6.25,6.00,5.50,5.00,4.50,4.00,3.50,3.00,2.50,2.00,1.75,1.50,1.25,1.00,0.75,0.50,0.25,0.00,0.25,0.50,0.75,1.00,1.25,1.50,1.75,2.00,2.50,3.00,3.50,4.00,4.50,5.00,5.50,6.00,6.25,6.50,6.75,7.00,7.25,7.50,7.75,8.00,7.75,7.50,7.25,7.00,5.25,3.50,1.75]` |

---

## 3) Graficos stem estilo MATLAB/Matplotlib

Para mantener legible la exportacion HTML, se muestra una vista resumida de la
forma global. El estilo sigue `stem`: baseline + varillas + marcadores.

### 3.1 Entrada `x[n]` (vista resumida)

<svg viewBox="0 0 760 280" width="100%" xmlns="http://www.w3.org/2000/svg">
  <rect x="0" y="0" width="760" height="280" fill="#ffffff"/>
  <text x="20" y="26" font-size="16" font-family="Georgia, 'Times New Roman', serif" fill="#111827">Entrada x[n] - estilo stem</text>
  <line x1="60" y1="230" x2="730" y2="230" stroke="#111827" stroke-width="1.4"/>
  <line x1="60" y1="40" x2="60" y2="230" stroke="#111827" stroke-width="1.0"/>
  <line x1="80" y1="230" x2="80" y2="150" stroke="#1f77b4" stroke-width="1.8"/>
  <line x1="116" y1="230" x2="116" y2="110" stroke="#1f77b4" stroke-width="1.8"/>
  <line x1="152" y1="230" x2="152" y2="70" stroke="#1f77b4" stroke-width="1.8"/>
  <line x1="188" y1="230" x2="188" y2="90" stroke="#1f77b4" stroke-width="1.8"/>
  <line x1="224" y1="230" x2="224" y2="110" stroke="#1f77b4" stroke-width="1.8"/>
  <line x1="260" y1="230" x2="260" y2="150" stroke="#1f77b4" stroke-width="1.8"/>
  <line x1="296" y1="230" x2="296" y2="190" stroke="#1f77b4" stroke-width="1.8"/>
  <line x1="332" y1="230" x2="332" y2="210" stroke="#1f77b4" stroke-width="1.8"/>
  <line x1="368" y1="230" x2="368" y2="230" stroke="#1f77b4" stroke-width="1.8"/>
  <line x1="404" y1="230" x2="404" y2="210" stroke="#1f77b4" stroke-width="1.8"/>
  <line x1="440" y1="230" x2="440" y2="190" stroke="#1f77b4" stroke-width="1.8"/>
  <line x1="476" y1="230" x2="476" y2="150" stroke="#1f77b4" stroke-width="1.8"/>
  <line x1="512" y1="230" x2="512" y2="110" stroke="#1f77b4" stroke-width="1.8"/>
  <line x1="548" y1="230" x2="548" y2="90" stroke="#1f77b4" stroke-width="1.8"/>
  <line x1="584" y1="230" x2="584" y2="70" stroke="#1f77b4" stroke-width="1.8"/>
  <line x1="620" y1="230" x2="620" y2="90" stroke="#1f77b4" stroke-width="1.8"/>
  <polyline points="80,150 116,110 152,70 188,90 224,110 260,150 296,190 332,210 368,230 404,210 440,190 476,150 512,110 548,90 584,70 620,90" fill="none" stroke="#1f77b4" stroke-width="1.6" stroke-dasharray="6 5" opacity="0.9"/>
  <circle cx="80" cy="150" r="4" fill="#ffffff" stroke="#1f77b4" stroke-width="2"/>
  <circle cx="116" cy="110" r="4" fill="#ffffff" stroke="#1f77b4" stroke-width="2"/>
  <circle cx="152" cy="70" r="4" fill="#ffffff" stroke="#1f77b4" stroke-width="2"/>
  <circle cx="188" cy="90" r="4" fill="#ffffff" stroke="#1f77b4" stroke-width="2"/>
  <circle cx="224" cy="110" r="4" fill="#ffffff" stroke="#1f77b4" stroke-width="2"/>
  <circle cx="260" cy="150" r="4" fill="#ffffff" stroke="#1f77b4" stroke-width="2"/>
  <circle cx="296" cy="190" r="4" fill="#ffffff" stroke="#1f77b4" stroke-width="2"/>
  <circle cx="332" cy="210" r="4" fill="#ffffff" stroke="#1f77b4" stroke-width="2"/>
  <circle cx="368" cy="230" r="4" fill="#ffffff" stroke="#1f77b4" stroke-width="2"/>
  <circle cx="404" cy="210" r="4" fill="#ffffff" stroke="#1f77b4" stroke-width="2"/>
  <circle cx="440" cy="190" r="4" fill="#ffffff" stroke="#1f77b4" stroke-width="2"/>
  <circle cx="476" cy="150" r="4" fill="#ffffff" stroke="#1f77b4" stroke-width="2"/>
  <circle cx="512" cy="110" r="4" fill="#ffffff" stroke="#1f77b4" stroke-width="2"/>
  <circle cx="548" cy="90" r="4" fill="#ffffff" stroke="#1f77b4" stroke-width="2"/>
  <circle cx="584" cy="70" r="4" fill="#ffffff" stroke="#1f77b4" stroke-width="2"/>
  <circle cx="620" cy="90" r="4" fill="#ffffff" stroke="#1f77b4" stroke-width="2"/>
</svg>

### 3.2 Filtro `h[k]` cuadrado (moving average)

<svg viewBox="0 0 760 240" width="100%" xmlns="http://www.w3.org/2000/svg">
  <rect x="0" y="0" width="760" height="240" fill="#ffffff"/>
  <text x="20" y="26" font-size="16" font-family="Georgia, 'Times New Roman', serif" fill="#111827">Kernel h[k] = [1, 1, 1, 1] - estilo stem</text>
  <line x1="60" y1="200" x2="500" y2="200" stroke="#111827" stroke-width="1.4"/>
  <line x1="60" y1="40" x2="60" y2="200" stroke="#111827" stroke-width="1.0"/>
  <line x1="140" y1="200" x2="140" y2="140" stroke="#ff7f0e" stroke-width="1.8"/>
  <line x1="220" y1="200" x2="220" y2="140" stroke="#ff7f0e" stroke-width="1.8"/>
  <line x1="300" y1="200" x2="300" y2="140" stroke="#ff7f0e" stroke-width="1.8"/>
  <line x1="380" y1="200" x2="380" y2="140" stroke="#ff7f0e" stroke-width="1.8"/>
  <polyline points="140,140 220,140 300,140 380,140" fill="none" stroke="#ff7f0e" stroke-width="1.6" stroke-dasharray="6 5" opacity="0.9"/>
  <circle cx="140" cy="140" r="4" fill="#ffffff" stroke="#ff7f0e" stroke-width="2"/>
  <circle cx="220" cy="140" r="4" fill="#ffffff" stroke="#ff7f0e" stroke-width="2"/>
  <circle cx="300" cy="140" r="4" fill="#ffffff" stroke="#ff7f0e" stroke-width="2"/>
  <circle cx="380" cy="140" r="4" fill="#ffffff" stroke="#ff7f0e" stroke-width="2"/>
</svg>

### 3.3 Salida `y[n]` (vista resumida)

<svg viewBox="0 0 760 300" width="100%" xmlns="http://www.w3.org/2000/svg">
  <rect x="0" y="0" width="760" height="300" fill="#ffffff"/>
  <text x="20" y="26" font-size="16" font-family="Georgia, 'Times New Roman', serif" fill="#111827">Salida y[n] - estilo stem</text>
  <line x1="60" y1="250" x2="730" y2="250" stroke="#111827" stroke-width="1.4"/>
  <line x1="60" y1="40" x2="60" y2="250" stroke="#111827" stroke-width="1.0"/>
  <line x1="80" y1="250" x2="80" y2="226" stroke="#2ca02c" stroke-width="1.8"/>
  <line x1="110" y1="250" x2="110" y2="190" stroke="#2ca02c" stroke-width="1.8"/>
  <line x1="140" y1="250" x2="140" y2="142" stroke="#2ca02c" stroke-width="1.8"/>
  <line x1="170" y1="250" x2="170" y2="100" stroke="#2ca02c" stroke-width="1.8"/>
  <line x1="200" y1="250" x2="200" y2="88" stroke="#2ca02c" stroke-width="1.8"/>
  <line x1="230" y1="250" x2="230" y2="100" stroke="#2ca02c" stroke-width="1.8"/>
  <line x1="260" y1="250" x2="260" y2="136" stroke="#2ca02c" stroke-width="1.8"/>
  <line x1="290" y1="250" x2="290" y2="172" stroke="#2ca02c" stroke-width="1.8"/>
  <line x1="320" y1="250" x2="320" y2="208" stroke="#2ca02c" stroke-width="1.8"/>
  <line x1="350" y1="250" x2="350" y2="226" stroke="#2ca02c" stroke-width="1.8"/>
  <line x1="380" y1="250" x2="380" y2="226" stroke="#2ca02c" stroke-width="1.8"/>
  <line x1="410" y1="250" x2="410" y2="208" stroke="#2ca02c" stroke-width="1.8"/>
  <line x1="440" y1="250" x2="440" y2="172" stroke="#2ca02c" stroke-width="1.8"/>
  <line x1="470" y1="250" x2="470" y2="136" stroke="#2ca02c" stroke-width="1.8"/>
  <line x1="500" y1="250" x2="500" y2="100" stroke="#2ca02c" stroke-width="1.8"/>
  <line x1="530" y1="250" x2="530" y2="82" stroke="#2ca02c" stroke-width="1.8"/>
  <line x1="560" y1="250" x2="560" y2="118" stroke="#2ca02c" stroke-width="1.8"/>
  <line x1="590" y1="250" x2="590" y2="160" stroke="#2ca02c" stroke-width="1.8"/>
  <line x1="620" y1="250" x2="620" y2="208" stroke="#2ca02c" stroke-width="1.8"/>
  <polyline points="80,226 110,190 140,142 170,100 200,88 230,100 260,136 290,172 320,208 350,226 380,226 410,208 440,172 470,136 500,100 530,82 560,118 590,160 620,208" fill="none" stroke="#2ca02c" stroke-width="1.6" stroke-dasharray="6 5" opacity="0.9"/>
  <circle cx="80" cy="226" r="4" fill="#ffffff" stroke="#2ca02c" stroke-width="2"/>
  <circle cx="110" cy="190" r="4" fill="#ffffff" stroke="#2ca02c" stroke-width="2"/>
  <circle cx="140" cy="142" r="4" fill="#ffffff" stroke="#2ca02c" stroke-width="2"/>
  <circle cx="170" cy="100" r="4" fill="#ffffff" stroke="#2ca02c" stroke-width="2"/>
  <circle cx="200" cy="88" r="4" fill="#ffffff" stroke="#2ca02c" stroke-width="2"/>
  <circle cx="230" cy="100" r="4" fill="#ffffff" stroke="#2ca02c" stroke-width="2"/>
  <circle cx="260" cy="136" r="4" fill="#ffffff" stroke="#2ca02c" stroke-width="2"/>
  <circle cx="290" cy="172" r="4" fill="#ffffff" stroke="#2ca02c" stroke-width="2"/>
  <circle cx="320" cy="208" r="4" fill="#ffffff" stroke="#2ca02c" stroke-width="2"/>
  <circle cx="350" cy="226" r="4" fill="#ffffff" stroke="#2ca02c" stroke-width="2"/>
  <circle cx="380" cy="226" r="4" fill="#ffffff" stroke="#2ca02c" stroke-width="2"/>
  <circle cx="410" cy="208" r="4" fill="#ffffff" stroke="#2ca02c" stroke-width="2"/>
  <circle cx="440" cy="172" r="4" fill="#ffffff" stroke="#2ca02c" stroke-width="2"/>
  <circle cx="470" cy="136" r="4" fill="#ffffff" stroke="#2ca02c" stroke-width="2"/>
  <circle cx="500" cy="100" r="4" fill="#ffffff" stroke="#2ca02c" stroke-width="2"/>
  <circle cx="530" cy="82" r="4" fill="#ffffff" stroke="#2ca02c" stroke-width="2"/>
  <circle cx="560" cy="118" r="4" fill="#ffffff" stroke="#2ca02c" stroke-width="2"/>
  <circle cx="590" cy="160" r="4" fill="#ffffff" stroke="#2ca02c" stroke-width="2"/>
  <circle cx="620" cy="208" r="4" fill="#ffffff" stroke="#2ca02c" stroke-width="2"/>
</svg>

---

## 4) Diferencia entre implementaciones

| Archivo | Estrategia | Observacion didactica |
|---|---|---|
| `non_recursive_conv.c` | Doble bucle `for` (`n` y `k`) | Mejor para mostrar implementacion clasica en embebidos |
| `recursive_conv.c` | Recursion en `n` + suma local en `for` | Muestra recursividad sin volver complejo el codigo |

Ambos programas (`non_recursive_conv.c` y `recursive_conv.c`) entregan exactamente la misma salida numerica para las 67 muestras de salida.

---

## 5) Referencias

Lyons, R. G. (1996). *Understanding digital signal processing*. Addison-Wesley Longman Publishing Co., Inc.

Datos editoriales del ejemplar usado en clase:
ISBN 978-0-201-63467-9, 544 paginas.
