# 🌈 esp8266_neopixel_smart_hub

![NeoPixel](https://img.shields.io/badge/LED-NeoPixel_WS2812B-red?style=for-the-badge)
![Connectivity](https://img.shields.io/badge/Connectivity-MQTT_%26_Web-blue?style=for-the-badge)
![Relays](https://img.shields.io/badge/Hardware-5_Channel_Relay-green?style=for-the-badge)

## 📖 Overview
The **esp8266_neopixel_smart_hub** is a high-end automation controller. It combines traditional appliance control (relays) with modern addressable LED lighting. This hub can serve as a central controller for a room, managing desk lights, ceiling fans, and providing visual notifications through the NeoPixel strip.



## 🚀 Key Features
* **✨ Addressable Lighting:** Controls 30 NeoPixels for rainbow cycles, color wipes, or status indicators.
* **🔌 Multi-Relay Control:** 4 standard ON/OFF relays and 1 PWM-capable channel (Relay 5) for dimming.
* **🔧 Zero-Config Setup:** If the home router is changed, the device automatically launches a web-based configuration page.
* **🏃 Intelligence (Logic Modes):**
  * **Mode 0 (Standard):** Motion sensor acts as a simple switch.
  * **Mode 1 (Timer):** Motion triggers the light for a specific duration (`LD`).
  * **Mode 2 (Manual):** All automation disabled for full user control.

## 🛠️ Hardware Setup
### Connection Map
| Component | Pin (ESP8266) | Function |
| :--- | :--- | :--- |
| **NeoPixel DIN** | GPIO 2 (D4) | Addressable Data |
| **Relay 1-4** | GPIO 4, 5, 0, 15 | Appliance Switching |
| **Relay 5 (Dimmer)** | GPIO 16 (D0) | PWM Output |
| **Motion Sensor** | GPIO 3 (RX) | Digital Input |
| **Buttons (KP)** | GPIO 14, 12, 13 | Local Control |



[Image of 5v Relay Module for Arduino]


## ⚠️ Power Management
When using 30 NeoPixels, they can draw up to **1.8A** at full brightness white. 
* **Do not** power the LED strip directly from the ESP8266 3.3V/5V pins. 
* Use an external 5V power supply and ensure a common ground between the power supply and the ESP8266.

## 👤 Author
* **Abdelrahman Elnahrawy**
* GitHub: [@Abdelrahman-Elnahrawy](https://github.com/Abdelrahman-Elnahrawy)

## ⚖️ License
This project is licensed under the **MIT License**.