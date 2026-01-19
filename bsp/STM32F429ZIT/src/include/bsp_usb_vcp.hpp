#ifndef BSP_USB_VCP_HPP_
#define BSP_USB_VCP_HPP_

#include <cstdint>
#include <span>

namespace bsp {

namespace usb_vcp {

void write(std::span<const uint8_t> data);

} // namespace usb_vcp

} // namespace bsp

#endif