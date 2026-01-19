#include "bsp.hpp"
#include "bsp_adc.hpp"
#include "bsp_led.hpp"
#include "gui.hpp"

namespace {

typedef struct {
  float alpha;
  float z0;
  float z1;
} SecondOrderEma;

SecondOrderEma ema;

volatile float rawAdcValue = 0;
volatile float lastAdcValue = 0;
float offset = 714.93823728f;

/**
 * Initialize the second-order EMA filter state.
 *
 * @param state The state of the second-order EMA filter.
 * @param alpha The smoothing factor (0 < alpha < 1).
 */
void EmaFilterInit(SecondOrderEma &state, float alpha) {
  state.alpha = alpha;
  state.z0 = 0.0f;
  state.z1 = 0.0f;
}

/**
 * Apply a single-order EMA filter to the input value.
 *
 * @param previousEma The previous EMA value.
 * @param newValue The new input value to be filtered.
 * @param alpha The smoothing factor (0 < alpha < 1).
 * @return The filtered output value.
 */
float EmaFilter(float previousEma, float newValue, float alpha) { return (alpha * newValue) + ((1.0f - alpha) * previousEma); }

/**
 * Apply a second-order EMA filter to the input value.
 *
 * @param state The state of the second-order EMA filter.
 * @param newValue The new input value to be filtered.
 * @return The filtered output value.
 */
float EmaFilterSecond(SecondOrderEma &state, float newValue) {
  state.z0 = EmaFilter(state.z0, newValue, state.alpha);
  state.z1 = EmaFilter(state.z1, state.z0, state.alpha);
  return state.z1;
}

/**
 * Convert raw ADC reading to current in µA
 *
 * Using the formula:
 * V_shunt = (Raw_ADC / Max_ADC_Reading) * (V_ref / Gain)
 * I = V_shunt / R_shunt
 *
 * @param rawValue Raw ADC reading.
 * @return Current in µA.
 */
float convertRawToCurrent(float rawValue) {
  float gain = 537.2f;
  float maxAdcReading = 65535.0f;
  float referenceVoltage = 3.3f;
  float shuntResistance = 1.0f;
  float voltage = (rawValue / maxAdcReading) * (referenceVoltage / gain);
  return (voltage * 1e6f) / shuntResistance; // in µA
}

/**
 * Convert raw ADC reading to voltage in V
 *
 * Using the formula:
 * V_out = (Raw_ADC / Max_ADC_Reading) * V_ref
 *
 * @param rawValue Raw ADC reading.
 * @return Voltage in V.
 */
float convertRawToVoltage(float rawValue) {
  float maxAdcReading = 65535.0f;
  float referenceVoltage = 3.3f;
  return (rawValue / maxAdcReading) * referenceVoltage;
}

} // namespace

int main(void) {
  bsp::init();
  gui::init();

  bool isCalibrated = bsp::adc::calibrate();
  if (!isCalibrated) {
    bsp::led::toggle();
    bsp::delayMs(5 * 1000);
    bsp::reset();
  }

  EmaFilterInit(ema, 0.005f);

  bsp::adc::readChannel([](uint32_t value) {
    float centered = static_cast<float>(value) - offset;
    rawAdcValue = EmaFilterSecond(ema, centered);
    lastAdcValue = rawAdcValue;
  });

  while (true) {
    bsp::adc::disableInterrupts();
    float filteredAdcValue = rawAdcValue;
    bsp::adc::enableInterrupts();

    float voltage = convertRawToVoltage(filteredAdcValue);
    gui::setVoltage(voltage);

    float current = convertRawToCurrent(filteredAdcValue);
    gui::setCurrent(current);

    gui::refresh();
    bsp::led::toggle();
  }
}
