#include "include/bsp.hpp"

#include "adc.h"
#include "gpio.h"
#include "i2c.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_adc.h"

extern "C" void SystemClock_Config(void);

namespace bsp {

void init() {
  HAL_Init();
  SystemClock_Config();

  MX_GPIO_Init();
  MX_ADC3_Init();
  MX_I2C3_Init();
}

int64_t getUptimeMs() { return HAL_GetTick(); }

void delayMs(int64_t ms) { HAL_Delay(static_cast<uint32_t>(ms)); }

} // namespace bsp