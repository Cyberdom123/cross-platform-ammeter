#include "bsp_led.hpp"

#include "main.h"
#include "stm32f4xx_hal.h"

namespace bsp {

namespace led {

void set(void) { HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET); }

void reset(void) { HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET); }

void toggle(void) { HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin); }

} // namespace led

} // namespace bsp
