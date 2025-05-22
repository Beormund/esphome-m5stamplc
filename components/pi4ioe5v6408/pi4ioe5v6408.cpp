#include "pi4ioe5v6408.h"
#include "esphome/core/log.h"

namespace esphome {
namespace pi4ioe5v6408 {

static const char *const TAG = "pi4ioe5v6408";

void PI4IOE5V6408Component::setup() {
  ESP_LOGD(TAG, "Setting up %s...", TAG);
  auto device_id = this->reg(PI4IOE5V6408_REG_DEVICE_ID).get();
  if ((device_id >> 2) != 0x28) {
    this->mark_failed();
    return;
  }
  this->reset_irq();
}

void PI4IOE5V6408Component::reset_irq() { this->reg(PI4IOE5V6408_REG_INTERRUPT_STATUS).get(); }

void PI4IOE5V6408Component::dump_config() {
  ESP_LOGCONFIG(TAG, "PI4IOE5V6408:");
  if (this->is_failed()) {
    ESP_LOGE(TAG, "Setting up PI4IOE5V6408 failed!");
  }
  LOG_I2C_DEVICE(this)
  ESP_LOGCONFIG(TAG, "  DID  %s", format_bin((uint8_t) this->reg(PI4IOE5V6408_REG_DEVICE_ID)).c_str());
  ESP_LOGCONFIG(TAG, "  IOD  %s", format_bin((uint8_t) this->reg(PI4IOE5V6408_REG_IO_DIRECTION)).c_str());
  ESP_LOGCONFIG(TAG, "  OUT  %s", format_bin((uint8_t) this->reg(PI4IOE5V6408_REG_OUTPUT_STATE)).c_str());
  ESP_LOGCONFIG(TAG, "  OHI  %s", format_bin((uint8_t) this->reg(PI4IOE5V6408_REG_OUTPUT_HIGH_IMPEDANCE)).c_str());
  ESP_LOGCONFIG(TAG, "  IDS  %s", format_bin((uint8_t) this->reg(PI4IOE5V6408_REG_INPUT_DEFAULT_STATE)).c_str());
  ESP_LOGCONFIG(TAG, "  UDE  %s", format_bin((uint8_t) this->reg(PI4IOE5V6408_REG_PULL_UP_DOWN_ENABLE)).c_str());
  ESP_LOGCONFIG(TAG, "  UDS  %s", format_bin((uint8_t) this->reg(PI4IOE5V6408_REG_PULL_UP_DOWN_SELECT)).c_str());
  ESP_LOGCONFIG(TAG, "  INS  %s", format_bin((uint8_t) this->reg(PI4IOE5V6408_REG_INPUT_STATUS)).c_str());
}

void PI4IOE5V6408Component::pin_mode(uint8_t pin, gpio::Flags flags) {
  if (this->is_failed())
    return;
  // Set 0 for Input; 1 for Output
  if ((flags & gpio::FLAG_OUTPUT) != 0) {
    this->reg(PI4IOE5V6408_REG_IO_DIRECTION) |= (1 << pin);
  } else if (flags & gpio::FLAG_INPUT != 0) {
    this->reg(PI4IOE5V6408_REG_IO_DIRECTION) &= ~(1 << pin);
  }
  // Set 0 for pull-down; 1 for pull-up
  if ((flags & gpio::FLAG_PULLUP) != 0) {
    this->reg(PI4IOE5V6408_REG_PULL_UP_DOWN_SELECT) |= (1 << pin);
  } else if (flags & gpio::FLAG_PULLDOWN !=0) {
    this->reg(PI4IOE5V6408_REG_PULL_UP_DOWN_SELECT) &= ~(1 << pin);
  }
  // 0 for low impedance; 1 for high impedance;
  if ((flags & gpio::FLAG_OPEN_DRAIN) != 0) {
    this->reg(PI4IOE5V6408_REG_OUTPUT_HIGH_IMPEDANCE) |= (1 << pin);
  } else {
    this->reg(PI4IOE5V6408_REG_OUTPUT_HIGH_IMPEDANCE) &= ~(1 << pin);
  }
}

void PI4IOE5V6408Component::digital_write(uint8_t pin, bool bit_value) {
  if (this->is_failed())
    return;
  if (bit_value) {
    this->reg(PI4IOE5V6408_REG_OUTPUT_STATE) |= (1 << pin);
  } else {
    this->reg(PI4IOE5V6408_REG_OUTPUT_STATE) &= ~(1 << pin);
  }
}

bool PI4IOE5V6408Component::digital_read(uint8_t pin) {
  if (!this->is_failed()) {
    return (this->reg(PI4IOE5V6408_REG_INPUT_STATUS).get() & (1 << pin)) != 0;
  }
  return false;
}

}  // namespace pi4ioe5v6408
}  // namespace esphome
