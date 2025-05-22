#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace pi4ioe5v6408 {

static const uint8_t PI4IOE5V6408_REG_DEVICE_ID = 0x01;
static const uint8_t PI4IOE5V6408_REG_IO_DIRECTION = 0x03;
static const uint8_t PI4IOE5V6408_REG_OUTPUT_STATE = 0x05;
static const uint8_t PI4IOE5V6408_REG_OUTPUT_HIGH_IMPEDANCE = 0x07;
static const uint8_t PI4IOE5V6408_REG_INPUT_DEFAULT_STATE = 0x09;
static const uint8_t PI4IOE5V6408_REG_PULL_UP_DOWN_ENABLE = 0x0B;
static const uint8_t PI4IOE5V6408_REG_PULL_UP_DOWN_SELECT = 0x0D;
static const uint8_t PI4IOE5V6408_REG_INPUT_STATUS = 0x0F;
static const uint8_t PI4IOE5V6408_REG_INTERRUPT_MASK = 0x11;
static const uint8_t PI4IOE5V6408_REG_INTERRUPT_STATUS = 0x13;

class PI4IOE5V6408Component : public Component, public i2c::I2CDevice {
 public:
  float get_setup_priority() const override { return setup_priority::HARDWARE; }
  void setup() override;
  void dump_config() override;
  void reset_irq();
  void pin_mode(uint8_t pin, gpio::Flags flags);
  void digital_write(uint8_t pin, bool bit_value);
  bool digital_read(uint8_t pin);

 protected:
  uint16_t value_{};
};

}  // namespace i4ioe5v6408
}  // namespace esphome
