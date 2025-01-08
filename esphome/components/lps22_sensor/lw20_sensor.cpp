#include "esphome/core/log.h"
#include "LW20.h"

namespace esphome
{
	namespace lw20_sensor
	{

		static const char *TAG = "lw20_sensor.sensor";

		void LW20Sensor::setup()
		{
			// Start serial monitor port.
			Serial.begin(115200);

			Serial.println("LW20 API Example");

			// Setup LW20.
			lw20.init();

			Serial.print("Model: ");
			Serial.print(lw20.getProductName());
			Serial.print(" - Firmware: ");
			Serial.print(lw20.getFirmwareVersion());
			Serial.print(" - Software: ");
			Serial.println(lw20.getSoftwareVersion());

			// Print list of parameters.
			Serial.print("Baud Rate: ");
			Serial.print(lw20BaudRateToInt(lw20.getComsBaudRate()));
			Serial.println("bps");
			Serial.print("Laser Offset: ");
			Serial.print(lw20.getLaserOffset());
			Serial.println("m");
			Serial.print("Alarm A Distance: ");
			Serial.print(lw20.getLaserAlarmA());
			Serial.println("m");
			Serial.print("Alarm B Distance: ");
			Serial.print(lw20.getLaserAlarmB());
			Serial.println("m");
			Serial.print("Alarm Hysteresis: ");
			Serial.print(lw20.getLaserAlarmHysteresis());
			Serial.println("m");
			Serial.print("Laser Mode: ");
			Serial.print(lw20ModeSpeedToInt(lw20.getLaserMode()));
			Serial.println("Hz");
			Serial.print("Laser Firing: ");
			Serial.println(lw20.getLaserFiring() ? "Yes" : "No");
			Serial.print("Background Noise: ");
			Serial.println(lw20.getLaserNoise());
			Serial.print("Temperature: ");
			Serial.print(lw20.getLaserTemperature());
			Serial.println(" degrees");
			Serial.print("Encoding Pattern: ");
			Serial.println((int)lw20.getLaserEncoding());
			Serial.print("Lost Confirmations: ");
			Serial.println(lw20.getLaserLostConfirmations());
			Serial.print("Gain Boost: ");
			Serial.println(lw20.getLaserGain());
			Serial.print("Servo Connected: ");
			Serial.println(lw20.getServoConnected() ? "Yes" : "No");
			Serial.print("Servo Scanning: ");
			Serial.println(lw20.getServoScanning() ? "Yes" : "No");
			Serial.print("Servo Position: ");
			Serial.print(lw20.getServoPosition());
			Serial.println(" degrees");
			Serial.print("Servo PWM Min: ");
			Serial.print(lw20.getServoPwmMin());
			Serial.println("us");
			Serial.print("Servo PWM Max: ");
			Serial.print(lw20.getServoPwmMax());
			Serial.println("us");
			Serial.print("Servo PWM Scale: ");
			Serial.print(lw20.getServoPwmScale());
			Serial.println("us/degree");
			Serial.print("Scan Type: ");
			Serial.println(lw20ScanTypeToStr(lw20.getServoScanType()));
			Serial.print("Servo Steps: ");
			Serial.print(lw20.getServoSteps());
			Serial.println(" steps/reading");
			Serial.print("Servo Lag: ");
			Serial.print(lw20.getServoLag());
			Serial.println(" degrees");
			Serial.print("Scan FOV Low: ");
			Serial.print(lw20.getServoFovLow());
			Serial.println(" degrees");
			Serial.print("Scan FOV High: ");
			Serial.print(lw20.getServoFovHigh());
			Serial.println(" degrees");
			Serial.print("Scan Alarm A Low: ");
			Serial.print(lw20.getServoAlarmALow());
			Serial.println(" degrees");
			Serial.print("Scan Alarm A High: ");
			Serial.print(lw20.getServoAlarmAHigh());
			Serial.println(" degrees");
			Serial.print("Scan Alarm B Low: ");
			Serial.print(lw20.getServoAlarmBLow());
			Serial.println(" degrees");
			Serial.print("Scan Alarm B High: ");
			Serial.print(lw20.getServoAlarmBHigh());
			Serial.println(" degrees");
			Serial.print("Laser Power On: ");
			Serial.println(lw20.getEnergyPower() ? "Yes" : "No");

			// Basic Setup.
			lw20.setLaserParams(LWMS_48);
		}

		void LW20Sensor::update()
		{
			float distance = lw20.getLaserDistance(LWPT_FIRST, LWRF_RAW);
			float temperature = lw20.getLaserTemperature();

			Serial.print("Temperature: ");
			Serial.println(temp.temperature);
			Serial.print("Dstance: ");
			Serial.print(pressure.pressure);
			Serial.println(" hPa");

			distance_sensor->publish_state(distance);
			temperature_sensor->publish_state(temperature);

			delay(100);
		}

		void LW20Sensor::dump_config()
		{
			ESP_LOGCONFIG(TAG, "LW20:");
			LOG_I2C_DEVICE(this);
			if (this->is_failed())
			{
				ESP_LOGE(TAG, "Communication with LW20 failed!");
			}
			LOG_UPDATE_INTERVAL(this);

			LOG_SENSOR("  ", "Temperature", this->temperature_sensor);
			LOG_SENSOR("  ", "Distance", this->distance_sensor);
		}

	} // namespace LW20Sensor
} // namespace esphome