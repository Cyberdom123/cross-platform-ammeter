#ifndef BSP_HPP_
#define BSP_HPP_

#include <cstdint>

namespace bsp {

void init();

int64_t getUptimeMs();

void delayMs(int64_t ms);

} // namespace bsp

#endif // BSP_HPP_