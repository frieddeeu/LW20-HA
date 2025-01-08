#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2c/i2c.h"

// ...
// Basic demo for pressure readings from Adafruit LPS2X
#include <Wire.h>

namespace esphome {
namespace lw20_sensor {

class LW20Sensor : public sensor::Sensor, public PollingComponent, public i2c::I2CDevice {
 public:
  void set_temperature_sensor(sensor::Sensor *temperature_sensor_) { temperature_sensor = temperature_sensor_; }
  void set_pressure_sensor(sensor::Sensor *pressure_sensor_) { pressure_sensor = pressure_sensor_; }
  
  LW20 lw20(Serial1, 115200);
  Sensor *temperature_sensor{nullptr}; // = new Sensor();
  Sensor *distance_sensor{nullptr}; // = new Sensor();
  LW20Sensor() : PollingComponent(15000) { }
  
  void setup() override;
  void update() override;
  void dump_config() override;
};

}  // namespace LPS22Sensor
}  // namespace esphome