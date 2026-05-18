"""Generate and visualize a sampled sinusoidal signal and its FFT magnitude spectrum."""
import numpy as np
import matplotlib.pyplot as plt

# Units and constants
_seg = float(1)
_mseg = _seg * (10**-3)
_HZ = float(1/_seg)
_kHz = _HZ * (10**3)

# System parameters
# IMPORTANTE: fs DEBE coincidir con la fs real del firmware (TIM3 en my_lib.c).
# Firmware: _BasePeriod(10) -> Ts = 100 us -> fs = 10 kHz.
# Si cambias el ARR de TIM3, actualiza este valor o la senal saldra reproducida
# a una frecuencia distinta (factor = fs_firmware / fs_python).
fs = 10 * _kHz # Sampling frequency (debe ser igual a la del MCU: 10 kHz)
Ts = 1/fs # Sampling period

# --- PWM hardware target (debe coincidir con my_lib.h del firmware) ----------
# Estos valores se usan para PRE-ESCALAR la senal directamente a cuentas de
# CCR1 y volcar la LUT como uint16_t. Asi el firmware no hace ninguna cuenta
# en runtime: solo `TIM1->CCR1 = ccr_table[i]`.
core_clk_hz       = 48_000_000   # SYSCLK del MCU (ver CORE_CLK en my_lib.h)
carrier_period_us = 1            # Periodo del PWM en us (ver Carrier_Period en my_lib.h)
pwm_arr           = round(core_clk_hz * carrier_period_us * 1e-6) - 1  # = 47 a 48 MHz/1us
pwm_period_counts = pwm_arr + 1                                        # = 48
print(f"PWM ARR = {pwm_arr}  ->  {pwm_period_counts} niveles de duty (paso {100/pwm_period_counts:.2f}%)")

# Signal parameters
fo = 50 * _HZ # Signal frequency
To = 1/fo # Signal period
A = 1.0 # Signal amplitude

# Buffer length
N = round(To/Ts)
print(f"Buffer length: {N} samples")

# Time vector
t = np.arange(0, N*Ts, Ts)
# Modulante: offset 0.5 + swing 0.4 -> rango natural [0.1, 0.9] (con A=1).
# Cambiala libremente (p. ej. una triangular); el resto del script y el firmware
# se adaptan via la LUT pre-escalada.
MOD_EXPR = "A * (0.5 + 0.4 * sin(2*pi*fo*t))"
#x_t = A * (0.5  + 0.4 * np.sin(2 * np.pi * fo * t))
# Triangular: rango [0.1, 0.9] con A=1
#x_t = A * (0.5 + 0.4 * (2 * np.abs(2 * ((t*fo) % 1) - 1) - 1))
x_t = A * (0.5 + 0.4 * np.sin(2 * np.pi * fo * t) * np.cos(2 * np.pi * 3*fo * t))
#x_t = A * (0.5 + 0.4 * (1 - (2 * np.pi * fo * (t - To/2))**2) * np.exp(- (2 * np.pi * fo * (t - To/2))**2 / 2))

# --- Wavelets como modulante --------------------------------------------------
# Dos wavelets canonicas, parametrizadas y centradas en t0. Devuelven la forma
# CRUDA (sin normalizar). El bloque de abajo elige una, la centra en To/2,
# resta DC residual y la escala linealmente al rango de duty [0.1, 0.9].
#
#   - Ricker (Mexican hat): segunda derivada (negada) de una gaussiana.
#       psi(tau) = (1 - (tau/sigma)^2) * exp(-(tau/sigma)^2 / 2)
#     Forma de "sombrero": un lobulo positivo central + dos lobulos negativos
#     simetricos. Sin oscilaciones internas. Espectro pasa-banda suave.
#
#   - Morlet (real): coseno modulado por gaussiana (wave packet).
#       psi(tau) = exp(-(tau/sigma)^2 / 2) * cos(2*pi*fc*tau)
#     Es la "wavelet" canonica visual: rafaga oscilante centrada con envolvente
#     gaussiana. fc controla el numero de ciclos dentro del paquete.
#def ricker_wavelet(tau, sigma):
#    u = tau / sigma
#    return (1.0 - u * u) * np.exp(-0.5 * u * u)

#def morlet_wavelet(tau, sigma, fc):
#    return np.exp(-0.5 * (tau / sigma) ** 2) * np.cos(2.0 * np.pi * fc * tau)

# --- Eleccion y parametros ----------------------------------------------------
# sigma se elige para que el paquete decaiga a ~0 en los bordes del periodo,
# garantizando un wrap-around suave en la LUT. Con sigma = To/10, en t=0 y t=To
# la envolvente vale exp(-(5)^2/2) ~= 3.7e-6 (practicamente cero).
sigma  = To / 10.0
fc_wav = 8.0 * fo                    # ~8 ciclos dentro del paquete Morlet
tau    = t - To / 2.0                # centrado en mitad del periodo

#psi   = ricker_wavelet(tau, sigma); MOD_EXPR = f"Ricker(tau, sigma=To/10), tau=t-To/2"
#psi    = morlet_wavelet(tau, sigma, fc_wav)
#MOD_EXPR = f"Morlet(tau, sigma=To/10, fc=8*fo), tau=t-To/2, normalizada a [0.1, 0.9]"

# Quito DC residual (el promedio del paquete sobre el periodo) para centrar el
# swing en 0.5 antes de escalar -> aprovecha al maximo el rango de duty.
#psi -= psi.mean()
#psi_peak = float(np.max(np.abs(psi)))
#x_t = A * (0.5 + 0.4 * psi / psi_peak)



# Pre-escalado a CCR1: x_t (en unidades de duty, 0..1 = 0..100%) se multiplica
# por pwm_period_counts para obtener cuentas del CCR1. Redondeo al entero mas
# cercano y saturacion a [0, pwm_period_counts] por seguridad.
ccr = np.clip(np.round(x_t * pwm_period_counts), 0, pwm_period_counts).astype(np.uint16)
print(f"x_t range: [{x_t.min():.3f}, {x_t.max():.3f}] (duty {100*x_t.min():.1f}%..{100*x_t.max():.1f}%)")
print(f"CCR range: [{ccr.min()}, {ccr.max()}] de 0..{pwm_period_counts}")

# Print signal buffer to console (los primeros valores de CCR para inspeccion)
print("ccr_table[0:16] = ", end="")
print("{", end="")
for i, val in enumerate(ccr[:16]):
    print(f"{int(val)}", end=", " if i < 15 else "")
print(", ...}")

# Write signal buffer to file — overwritten on every run
# Output goes directly into the firmware source tree so the build picks it up.
VALS_PER_LINE = 16
INDENT = "\t\t\t\t\t\t"
OUT_PATH = "analog_pwm/Src/signal_array.c"
with open(OUT_PATH, "w", encoding="utf-8") as f_out:
    f_out.write("/* Auto-generated by gen_signal.py — DO NOT EDIT BY HAND. */\n")
    f_out.write('#include "main.h"\n\n')
    f_out.write(
        f"/* PWM target: SYSCLK={core_clk_hz} Hz, Carrier={carrier_period_us} us, "
        f"ARR={pwm_arr} ({pwm_period_counts} niveles -> paso {100/pwm_period_counts:.2f}%).\n"
        f"   Senal:  fs={fs:.0f} Hz (Ts={Ts*1e6:.1f} us), fo={fo:.0f} Hz, N={N} muestras, A={A}.\n"
        f"   Modulante: x(t) = {MOD_EXPR}\n"
        f"   Rango duty real: {100*x_t.min():.1f}%..{100*x_t.max():.1f}%  ->  CCR1 en [{int(ccr.min())}, {int(ccr.max())}].\n"
        f"   Para regenerar: python gen_signal.py (debe coincidir CORE_CLK y Carrier_Period con my_lib.h). */\n\n"
    )
    f_out.write("const uint16_t ccr_table[] = {")
    for i, val in enumerate(ccr):
        if i > 0 and i % VALS_PER_LINE == 0:
            f_out.write("\n" + INDENT)
        f_out.write(f"{int(val)}")
        if i < len(ccr) - 1:
            f_out.write(", ")
    f_out.write("};\n\n")
    f_out.write(f"const uint32_t ccr_len = {N}u;\n")
print(f"Buffer written to {OUT_PATH}")

# FFT of the signal
X_f = np.fft.fft(x_t)
abs_X_f = np.abs(X_f)
f = np.fft.fftfreq(N, d=Ts)

# Single-sided amplitude spectrum: keep non-negative frequencies
pos = f >= 0
f_pos = f[pos]
mag_pos = (1/N) * abs_X_f[pos]
# Double non-DC and non-Nyquist bins so magnitudes equal actual amplitudes
if N % 2 == 0:
    mag_pos[1:-1] *= 2   # even N: last positive bin is Nyquist — leave it
else:
    mag_pos[1:] *= 2     # odd N: no Nyquist bin

# Combined figure with two subplots
fig, axes = plt.subplots(2, 1, figsize=(10, 7))

# --- Time-domain plot ---
ml, sl, bl = axes[0].stem(t / _mseg, x_t, markerfmt='C0o', linefmt='C0-', basefmt='none')
ml.set_markersize(5)
sl.set_linewidth(1.0)
axes[0].set_xlabel('Time [ms]')
axes[0].set_ylabel('Amplitude')
axes[0].set_title(
    f'Sampled Signal  (fo = {fo:.0f} Hz, fs = {fs/_kHz:.0f} kHz, '
    f'N = {N} samples, To = {To/_mseg:.1f} ms)'
)
t_max_ms = N * Ts / _mseg
axes[0].set_xlim(left=-t_max_ms * 0.05, right=t_max_ms * 1.05)
axes[0].set_ylim(
    bottom=x_t.min() - 0.30 * (x_t.max() - x_t.min()),
    top=x_t.max()    + 0.30 * (x_t.max() - x_t.min())
)
axes[0].grid(True, linestyle='--', alpha=0.5)

# Annotate peak and trough
i_max = int(np.argmax(x_t))
i_min = int(np.argmin(x_t))
for idx, offset, va in [(i_max, 8, 'bottom'), (i_min, -8, 'top')]:
    axes[0].annotate(
        f'{x_t[idx]:.3f}\n{t[idx] / _mseg:.2f} ms',
        xy=(t[idx] / _mseg, x_t[idx]),
        xytext=(0, offset),
        textcoords='offset points',
        ha='center', va=va,
        fontsize=8, color='C0'
    )

# --- Frequency-domain plot ---
# Zoom FFT view: show up to 5× the signal frequency
f_view_max = 5 * fo
view_mask = f_pos <= f_view_max
f_view = f_pos[view_mask]
mag_view = mag_pos[view_mask]

ml2, sl2, bl2 = axes[1].stem(f_view, mag_view, markerfmt='C1o', linefmt='C1-', basefmt='none')
ml2.set_markersize(5)
sl2.set_linewidth(1.0)
axes[1].set_xlabel('Frequency [Hz]')
axes[1].set_ylabel('Magnitude')
axes[1].set_title(f'FFT Magnitude Spectrum  (single-sided, zoomed to {f_view_max:.0f} Hz)')
axes[1].set_xlim(left=-fo * 0.1, right=f_view_max * 1.1)
axes[1].set_ylim(bottom=0, top=mag_view.max() * 1.40)
axes[1].grid(True, linestyle='--', alpha=0.5)

# Annotate prominent peaks (magnitude above 1 % of max)
peak_thresh = 0.01 * mag_view.max() if mag_view.max() > 0 else 0
for freq, mag in zip(f_view, mag_view):
    if mag >= peak_thresh:
        axes[1].annotate(
            f'{mag:.3f}\n{freq:.0f} Hz',
            xy=(freq, mag),
            xytext=(0, 8),
            textcoords='offset points',
            ha='center', va='bottom',
            fontsize=8, color='C1'
        )

plt.tight_layout(pad=2.0, h_pad=4.5)
plt.show()
