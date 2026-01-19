#include "include/bsp.hpp"

#include "SEGGER_RTT.h"
#include "adc.h"
#include "gpio.h"
#include "i2c.h"
#include "stm32g4xx_hal.h"
#include "stm32g4xx_hal_adc.h"

extern "C" void SystemClock_Config(void);

namespace bsp {

void init() {
  HAL_Init();
  SystemClock_Config();

  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();

  SEGGER_RTT_Init();
  HAL_Delay(100);
}

int64_t getUptimeMs() { return HAL_GetTick(); }

void delayMs(int64_t ms) { HAL_Delay(static_cast<uint32_t>(ms)); }

void reset() { NVIC_SystemReset(); }

} // namespace bsp