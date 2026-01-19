#ifndef SSD1306_DISPLAY_PORT_HPP_
#define SSD1306_DISPLAY_PORT_HPP_

#include <cstddef>
#include <cstdint>

namespace ssd1306 {

void WriteCommand(uint8_t byte);

void WriteData(uint8_t *buffer, size_t buff_size);

} // namespace ssd1306

#endif