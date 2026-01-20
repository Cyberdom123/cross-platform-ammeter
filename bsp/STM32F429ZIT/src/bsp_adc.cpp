#include "bsp_adc.hpp"

#include "adc.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_adc.h"
#include "stm32f4xx_hal_adc_ex.h"
#include "stm32f4xx_hal_def.h"
#include <cstdint>
#include <signal.h>

enum {
  ADC_CHANNEL_COUNT = 2,
};

volatile bsp::adc::OnConversion onConversionComplete = nullptr;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *) {
  uint32_t value = HAL_ADC_GetValue(&hadc3);
  if (onConversionComplete) {
    onConversionComplete(value);
  }
}

namespace bsp::adc {

bool calibrate(void) { return true; }

uint32_t readChannelPolling() {
  HAL_ADC_Start(&hadc3);
  if (HAL_OK == HAL_ADC_PollForConversion(&hadc3, HAL_MAX_DELAY)) {
    return HAL_ADC_GetValue(&hadc3);
  }
  return 0;
}

void disableInterrupts() { HAL_NVIC_DisableIRQ(ADC_IRQn); }

void enableInterrupts() { HAL_NVIC_EnableIRQ(ADC_IRQn); }

void readChannel(OnConversion callback) {
  onConversionComplete = callback;
  HAL_ADC_Start_IT(&hadc3);
}

}; // namespace bsp::adc