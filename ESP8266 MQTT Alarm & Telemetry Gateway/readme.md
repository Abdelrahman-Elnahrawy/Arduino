# 📡 ESP8266 IR Transmitter with WiFi & MQTT

![ESP8266](https://img.shields.io/badge/ESP8266-IoT-black?style=for-the-badge&logo=espressif)
![MQTT](https://img.shields.io/badge/Protocol-MQTT-660066?style=for-the-badge&logo=mqtt)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)
![Author](https://img.shields.io/badge/Author-Abdelrahman--Elnahrawy-orange?style=for-the-badge)

## 📖 Overview
Transform your ESP8266 into a **Universal Smart Remote**! This project allows you to control Infrared (IR) devices—such as TVs, Air Conditioners, and Sound Systems—remotely via **WiFi** using the **MQTT** protocol. 

By connecting this to a home automation platform like Home Assistant or OpenHAB, you can bridge the gap between "dumb" IR devices and your smart home ecosystem.

## 🚀 Features
* 🌐 **Wireless Control:** Send IR commands from any device on your network.
* 🤖 **Home Automation Ready:** Full MQTT integration for seamless smart home logic.
* 📡 **Multi-Protocol:** Supports major IR protocols (NEC, Sony, Samsung, Panasonic, etc.) via the `IRremoteESP8266` library.
* ⚡ **Real-time Feedback:** Reports status and command execution back to the MQTT broker.

## 🛠️ Hardware Requirements
| Component | Purpose |
| :--- | :--- |
| **ESP8266** | Brains and WiFi connectivity (NodeMCU/Wemos D1 Mini). |
| **IR Transmitter LED** | 940nm Infrared LED to send the signal. |
| **2N2222 Transistor** | Used as a switch to provide enough current to the IR LED. |
| **Resistors** | 100Ω (for LED) and 1kΩ (for Transistor Base). |

## 🔌 Circuit Connection
* **IR LED Anode:** To 5V (via 100Ω resistor).
* **IR LED Cathode:** To Collector of 2N2222.
* **Transistor Emitter:** To GND.
* **Transistor Base:** To **GPIO 4 (D2)** via 1kΩ resistor.

## ⚙️ Software Configuration
Before uploading, ensure you update the following in the code:
1.  **WiFi Credentials:** `ssid` and `password`.
2.  **MQTT Broker:** `mqtt_server` (IP address of your broker/Pi).
3.  **Topics:** Define your command topics (e.g., `home/livingroom/tv/cmd`).

## 📨 MQTT Usage Example
To turn on a TV using the NEC protocol:
* **Topic:** `home/ir/send`
* **Payload:** `NEC:0x20DF10EF`

## 👤 Author
* **Abdelrahman Elnahrawy**
* GitHub: [@Abdelrahman-Elnahrawy](https://github.com/Abdelrahman-Elnahrawy)

## ⚖️ License
This project is licensed under the **MIT License**.
