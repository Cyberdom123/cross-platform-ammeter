#include "ssd1306_display_port.hpp"
#include "bsp_display_bus.hpp"

namespace ssd1306 {

void WriteCommand(uint8_t command) { bsp::displayBus::write(0x3C, 0x00, &command, 1); }

void WriteData(uint8_t *buffer, size_t size) { bsp::displayBus::write(0x3C, 0x40, buffer, size); }

} // namespace ssd1306
