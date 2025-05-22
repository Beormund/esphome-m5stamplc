#pragma once

#include "esphome/components/pi4ioe5v6408/pi4ioe5v6408.h"

namespace esphome {
namespace pi4ioe5v6408 {

class PI4IOE5V6408Component;

class PI4IOE5V6408GPIOPin : public GPIOPin {
 public:
  void setup() override;
  void pin_mode(gpio::Flags flags) override;  
  bool digital_read() override;
  void digital_write(bool value) override;
  void set_parent(PI4IOE5V6408Component *parent) { parent_ = parent; }
  void set_pin(uint8_t pin) { pin_ = pin; }
  void set_inverted(bool inverted) { inverted_ = inverted; }
  void set_flags(gpio::Flags flags) { flags_ = flags; }
  gpio::Flags get_flags() const override { return this->flags_; }
  std::string dump_summary() const override;

 protected:
  PI4IOE5V6408Component *parent_;
  uint8_t pin_;
  bool inverted_;
  gpio::Flags flags_;
};

}  // namespace pi4ioe5v6408
}  // namespace esphome
