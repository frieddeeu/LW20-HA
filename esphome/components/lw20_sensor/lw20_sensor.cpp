#include "lw20_sensor.h"
#include "esphome/core/log.h"

namespace esphome {
namespace lw20_sensor {

static const char *TAG = "lw20_sensor.sensor";

void LW20Sensor::setup() {
    ESP_LOGCONFIG(TAG, "Setting up LW20...");

    if (!this->lw20.init()) {
        ESP_LOGE(TAG, "Failed to initialize LW20 sensor!");
        return;
    }

    ESP_LOGCONFIG(TAG, "Model: %s, Firmware: %s", this->lw20.getProductName(), this->lw20.getFirmwareVersion());
    this->lw20.setLaserParams(LWMS_48);
}

void LW20Sensor::update() {
    float distance = this->lw20.getLaserDistance(LWPT_FIRST, LWRF_RAW);
    float temperature = this->lw20.getLaserTemperature();

    if (this->distance_sensor) {
        this->distance_sensor->publish_state(distance);
    }
    if (this->temperature_sensor) {
        this->temperature_sensor->publish_state(temperature);
    }

    ESP_LOGD(TAG, "Distance: %.2f m, Temperature: %.2f °C", distance, temperature);
}

void LW20Sensor::dump_config() {
    ESP_LOGCONFIG(TAG, "LW20 Sensor Configuration:");
    LOG_SENSOR("  ", "Temperature", this->temperature_sensor);
    LOG_SENSOR("  ", "Distance", this->distance_sensor);
}

}  // namespace lw20_sensor
}  // namespace esphome
