#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2c/i2c.h"
#include <Wire.h>
#include <LW20.h>

namespace esphome {
namespace lw20_sensor {

class LW20Sensor : public sensor::Sensor, public PollingComponent, public i2c::I2CDevice {
 public:
  LW20Sensor() : PollingComponent(15000), lw20(&Serial1) {}

  void set_temperature_sensor(sensor::Sensor *temperature_sensor_) { temperature_sensor = temperature_sensor_; }
  void set_distance_sensor(sensor::Sensor *distance_sensor_) { distance_sensor = distance_sensor_; }

  void setup() override;
  void update() override;
  void dump_config() override;

 private:
  LW20 lw20;
  sensor::Sensor *temperature_sensor{nullptr};
  sensor::Sensor *distance_sensor{nullptr};
};

}  // namespace lw20_sensor
}  // namespace esphome
