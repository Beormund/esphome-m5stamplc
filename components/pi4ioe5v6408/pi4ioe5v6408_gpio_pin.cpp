#include "pi4ioe5v6408_gpio_pin.h"

namespace esphome {
namespace pi4ioe5v6408 {

static const char *const TAG = "pi4ioe5v6408_gpio_pin";

void PI4IOE5V6408GPIOPin::setup() { pin_mode(flags_); }
void PI4IOE5V6408GPIOPin::pin_mode(gpio::Flags flags) { this->parent_->pin_mode(this->pin_, flags); }
bool PI4IOE5V6408GPIOPin::digital_read() { return this->parent_->digital_read(this->pin_) != this->inverted_; }
void PI4IOE5V6408GPIOPin::digital_write(bool value) {
  this->parent_->digital_write(this->pin_, value != this->inverted_);
}
std::string PI4IOE5V6408GPIOPin::dump_summary() const {
  char buffer[32];
  snprintf(buffer, sizeof(buffer), "%u via pi4ioe5v6408", pin_);
  return buffer;
}

}  // namespace pi4ioe5v6408
}  // namespace esphome
