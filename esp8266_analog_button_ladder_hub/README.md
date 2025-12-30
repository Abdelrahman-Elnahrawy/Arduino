# 🎹 ESP8266 Analog Ladder Hub

![Analog](https://img.shields.io/badge/Interface-Analog_Button_Ladder-orange?style=for-the-badge)
![Efficiency](https://img.shields.io/badge/Hardware-Pin_Optimization-green?style=for-the-badge)
![MQTT](https://img.shields.io/badge/Data-MQTT_Telemetry-blue?style=for-the-badge)

## 📖 Overview
The **Analog Ladder Hub** is a masterclass in pin efficiency. Since the ESP8266 only has one Analog-to-Digital Converter (ADC), this project uses a resistor ladder to read 6 different buttons on a single pin. Furthermore, it uses a "Mode Relay" to physically switch the ADC between the button network and a temperature sensor, effectively multiplexing the hardware.



## 🚀 Key Features
* **📉 Resistor Ladder Interface:** Decodes multiple button presses based on voltage division.
* **🔄 Hardware Multiplexing:** Uses `relaymod` to toggle the $A0$ pin between reading user input and reading ambient temperature.
* **💡 Dimming Control:** Includes a PWM channel for variable brightness or motor speed control.
* **📡 Real-time Feedback:** Publishes PIR motion alerts and relay states to an MQTT broker every 2 seconds.

## 🛠️ Hardware Architecture
### The Button Ladder
By using different resistor values (e.g., 1k, 2k, 4.7k, 10k), each button creates a specific $V_{out}$ that the ESP8266 reads as a value between 0 and 1023.



### Pin Definitions
| Component | Pin | Function |
| :--- | :--- | :--- |
| **ADC Input** | A0 | Buttons & Temp Sensor |
| **Mode Relay** | D2 | ADC Source Switch |
| **Digital Relays** | D6, D7, D5, D8, D3 | On/Off Appliances |
| **PWM Output** | D0 | Dimmer |
| **PIR Sensor** | D4 | Motion Detection |

## 👤 Author
* **Abdelrahman Elnahrawy**
* GitHub: [@Abdelrahman-Elnahrawy](https://github.com/Abdelrahman-Elnahrawy)

## ⚖️ License
MIT License