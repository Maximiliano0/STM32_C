#include "main.h"

/* Global variables ----*/
extern uint32_t sampling;

// Example FIR filter settings
#define FILTER_TAP_NUM 5

// Example FIR filter coefficients (low-pass)
const float firCoeffs[FILTER_TAP_NUM] = {
    0.2f, 0.2f, 0.2f, 0.2f, 0.2f
};

// Circular buffer to store input samples
float firBuffer[FILTER_TAP_NUM] = {0};
uint8_t bufferIndex = 0;

// Function to apply FIR filter
float FIR_Filter(float input) {
    float output = 0.0f;
    uint8_t idx = bufferIndex;

    // Add new sample into Buffer
    firBuffer[bufferIndex] = input;

    // Perform the convolution
    for (int i = 0; i < FILTER_TAP_NUM; i++) {
        output += firCoeffs[i] * firBuffer[idx];
        if (idx == 0)
            idx = FILTER_TAP_NUM - 1;
        else
            idx--;
    }

    bufferIndex++;
    if (bufferIndex >= FILTER_TAP_NUM) {
        bufferIndex = 0;
    }

    return output;
}

/* Main Function ----*/
int main(void)
{
	float new_sample, filtered_value;

    // Hardware Initialize
    Hw_Init();

    // Sampling Tick
    sampling = ADC_Sampling_Period;

    // Infinite Loop
    while (1)
    {
        if (sampling == 0)
        {
        	// Assume we read a new ADC value here
            new_sample = ADC_Read();
            // Apply FIR filter
            filtered_value = FIR_Filter(new_sample);
        }
    }

}
