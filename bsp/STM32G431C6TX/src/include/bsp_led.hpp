#ifndef BSP_GPIO_HPP_
#define BSP_GPIO_HPP_

#include <cstdint>

namespace bsp {

namespace led {

void set(void);

void reset(void);

void toggle(void);

} // namespace led

} // namespace bsp

#endif // BSP_GPIO_HPP_