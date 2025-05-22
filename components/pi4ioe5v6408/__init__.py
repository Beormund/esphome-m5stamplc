import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.components import i2c
from esphome.const import (
    CONF_ID,
    CONF_NUMBER,
    CONF_MODE,
    CONF_INVERTED,
)

CONF_PI4IOE5V6408 = "pi4ioe5v6408"
DEPENDENCIES = ["i2c"]
MULTI_CONF = True

pi4ioe5v6408_ns = cg.esphome_ns.namespace(CONF_PI4IOE5V6408)
PI4IOE5V6408Component = pi4ioe5v6408_ns.class_("PI4IOE5V6408Component", cg.Component, i2c.I2CDevice)
PI4IOE5V6408GPIOPin = pi4ioe5v6408_ns.class_("PI4IOE5V6408GPIOPin", cg.GPIOPin)

CONFIG_SCHEMA = (
    cv.Schema({cv.Required(CONF_ID): cv.declare_id(PI4IOE5V6408Component)})
    .extend(cv.COMPONENT_SCHEMA)
    .extend(i2c.i2c_device_schema(0x43))
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
    return var

PI4IOE5V6408_PIN_SCHEMA = (
    pins.gpio_base_schema(
        pin_type = PI4IOE5V6408GPIOPin, 
        number_validator = cv.int_range(min=0, max=7)
    )
    .extend({cv.Required(CONF_PI4IOE5V6408): cv.use_id(PI4IOE5V6408Component)})
)

@pins.PIN_SCHEMA_REGISTRY.register(CONF_PI4IOE5V6408, PI4IOE5V6408_PIN_SCHEMA)
async def pi4ioe5v6408_pin_to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    parent = await cg.get_variable(config[CONF_PI4IOE5V6408])
    cg.add(var.set_parent(parent))
    num = config[CONF_NUMBER]
    cg.add(var.set_pin(num))
    cg.add(var.set_inverted(config[CONF_INVERTED]))
    cg.add(var.set_flags(pins.gpio_flags_expr(config[CONF_MODE])))
    return var
