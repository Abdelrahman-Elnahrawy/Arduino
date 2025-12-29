This project implements a multi-channel airflow monitoring system using an ESP8266. It reads and processes data from multiple airflow sensors, applies basic filtering and calibration, and prepares the data for monitoring, logging, or transmission.

The system is designed to continuously sample airflow values, convert raw sensor readings into meaningful airflow data, and make them available for further use such as display, alarms, or network communication.

🔧 Key Features

Supports multiple airflow sensor inputs

Continuous sensor sampling using non-blocking logic

Conversion of raw analog values into airflow measurements

Simple filtering / averaging to stabilize readings

Modular structure for easy expansion or sensor replacement

Suitable for real-time monitoring applications

🧠 How It Works

ESP8266 initializes all airflow sensor input channels

Analog readings are taken periodically from each sensor

Raw ADC values are processed and scaled to airflow units

Processed airflow data is stored and updated continuously

The system can be extended to send data via Wi-Fi, MQTT, or display it locally

🧩 Libraries Used

ESP8266WiFi.h (if networking is enabled)

Standard Arduino core libraries

🎯 Typical Use Cases

HVAC airflow monitoring

Ventilation system diagnostics

Industrial air flow measurement

Environmental monitoring projects

Smart building automation nodes