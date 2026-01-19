#ifndef BSP_ADC_HPP_
#define BSP_ADC_HPP_

#include <array>
#include <cstdint>
#include <cstdlib>

namespace bsp {

namespace adc {

/**
 * Read ADC value using polling method.
 *
 * @param channel ADC channel to read from.
 * @return Raw ADC value.
 */
uint32_t readChannelPolling(uint8_t channel);

} // namespace adc

} // namespace bsp

#endif // BSP_ADC_HPP_