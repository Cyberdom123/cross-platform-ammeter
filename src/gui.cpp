#include "gui.hpp"
#include "bsp.hpp"

#include "ssd1306_display.hpp"
#include "ssd1306_display_fonts.hpp"

#include <cstdint>
#include <format>
#include <string>

namespace {
char buffer[128];
}

namespace gui {

void init(void) { ssd1306::Init(); }

void showCredits(void) {
  ssd1306::Fill(ssd1306::Black);
  ssd1306::SetCursor(5, 20);
  ssd1306::WriteString("PicoAmmeter", ssd1306::Font_16x15, ssd1306::White);
  ssd1306::UpdateScreen();
  bsp::delayMs(1000);
}

void setCurrent(float current) {
  if (current < 0) {
    current = 0;
  }

  bool isInPicoAmps = (current <= 9.999);                   // 0 to ~10 µA
  bool isInNanoAmps = (current > 9.999 && current < 999.9); // 10 µA to ~1 mA
  bool isInMicroAmps = (current >= 999.9);                  // 1 mA and above

  ssd1306::SetCursor(0, 0);

  if (isInPicoAmps) {
    std::snprintf(buffer, sizeof(buffer), "%0.4fuA", current);
  } else if (isInNanoAmps) {
    std::snprintf(buffer, sizeof(buffer), "%0.2fuA", current);
  } else if (isInMicroAmps) {
    std::snprintf(buffer, sizeof(buffer), "%0.4fmA", current / 1000.0f);
  } else {
    std::snprintf(buffer, sizeof(buffer), "err");
  }

  ssd1306::WriteString(buffer, ssd1306::Font_16x24, ssd1306::White);
}

void setVoltage(float voltage) {
  if (voltage < 0) {
    voltage = 0;
  }

  ssd1306::SetCursor(0, 30);
  std::snprintf(buffer, sizeof(buffer), "%0.5fV", voltage);
  ssd1306::WriteString(buffer, ssd1306::Font_16x24, ssd1306::White);
}

void refresh(void) {
  ssd1306::UpdateScreen();
  ssd1306::Fill(ssd1306::Black);
}

} // namespace gui