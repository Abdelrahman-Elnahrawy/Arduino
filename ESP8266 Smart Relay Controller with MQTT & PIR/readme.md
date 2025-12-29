# 🏠 ESP8266 Smart Relay Controller with MQTT & PIR

![ESP8266](https://img.shields.io/badge/ESP8266-Automation-black?style=for-the-badge&logo=espressif)
![Arduino IDE](https://img.shields.io/badge/Arduino_IDE-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![MQTT](https://img.shields.io/badge/Protocol-MQTT-660066?style=for-the-badge&logo=mqtt)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)
![Author](https://img.shields.io/badge/Author-Abdelrahman--Elnahrawy-orange?style=for-the-badge)

## 📖 Overview
This project creates an **Intelligent Motion-Sensing Switch**. It combines an ESP8266 with a PIR (Passive Infrared) sensor to detect occupancy and control a high-voltage relay. 

Unlike a standard motion light, this system is "Smart"—it reports motion events to an **MQTT Broker** and allows you to manually override the relay state via a smartphone or dashboard (like Home Assistant).

## 🚀 Features
* **🏃 Motion Activation:** Automatically toggles lights/appliances when someone enters the room.
* **📲 Remote Override:** Force the Relay ON or OFF via MQTT messages, bypassing the sensor.
* **⏲️ Configurable Timeout:** Set how long the relay stays active after the last motion is detected.
* **🌐 IoT Integrated:** Sends "Motion Detected" and "Relay State" updates to your smart home server.

## 🛠️ Hardware Requirements
| Component | Purpose |
| :--- | :--- |
| **ESP8266** | WiFi connectivity and logic processing. |
| **PIR Sensor (HC-SR501)** | Detects human infrared heat signatures. |
| **Relay Module (5V/3.3V)** | Switches high-voltage AC loads (Lights, Fans). |
| **Status LED** | Local visual indicator of connectivity or motion. |

## 🔌 Circuit Connection
* **PIR Sensor VCC:** 5V (or 3.3V depending on model)
* **PIR Sensor OUT:** **GPIO 4 (D2)**
* **Relay IN:** **GPIO 5 (D1)**
* **Relay VCC/GND:** 5V and GND



## ⚙️ Logic Workflow
1. **Auto Mode:** If the PIR detects motion, the Relay triggers and a timer starts.
2. **Telemetry:** The ESP8266 publishes `motion: ON` to the MQTT topic.
3. **MQTT Control:** If a message `toggle: OFF` is received, the relay shuts down regardless of the PIR state.

## 👤 Author
* **Abdelrahman Elnahrawy**
* GitHub: [@Abdelrahman-Elnahrawy](https://github.com/Abdelrahman-Elnahrawy)

## ⚖️ License
This project is licensed under the **MIT License**.
