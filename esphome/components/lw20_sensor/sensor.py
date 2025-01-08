import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, sensor
from esphome.const import CONF_ID, ICON_EMPTY, UNIT_EMPTY, UNIT_HECTOPASCAL, UNIT_CELSIUS,  CONF_TEMPERATURE, CONF_DISTANCE, DEVICE_CLASS_DISTANCE, DEVICE_CLASS_TEMPERATURE, STATE_CLASS_MEASUREMENT

DEPENDENCIES = ['uart']

lw20_sensor = cg.esphome_ns.namespace('lw20_sensor')
LW20Sensor = lw20_sensor.class_('LW20Sensor', cg.PollingComponent, uart.UARTDevice)
CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(LW20Sensor),
            cv.Required(CONF_TEMPERATURE): sensor.sensor_schema(
                unit_of_measurement=UNIT_CELSIUS,
                accuracy_decimals=1,
                device_class=DEVICE_CLASS_TEMPERATURE,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Required(CONF_DISTANCE): sensor.sensor_schema(
                unit_of_measurement=UNIT_HECTOPASCAL,
                accuracy_decimals=1,
                device_class=DEVICE_CLASS_DISTANCE,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
#            cv.Optional(CONF_HEATER_ENABLED, default=False): cv.boolean,
        },
    )
    .extend(cv.polling_component_schema("60s"))
    .extend(uart.UART_DEVICE_SCHEMA)
)
async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
#    await sensor.register_sensor(var, config)
    await uart.register_uart_device(var, config)


    if CONF_TEMPERATURE in config:
        sens = await sensor.new_sensor(config[CONF_TEMPERATURE])
        cg.add(var.set_temperature_sensor(sens))

    if CONF_DISTANCE in config:
        sens = await sensor.new_sensor(config[CONF_DISTANCE])
        cg.add(var.set_distance_sensor(sens))