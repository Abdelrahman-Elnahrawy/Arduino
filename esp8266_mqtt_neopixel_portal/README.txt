# 🌐 esp8266_mqtt_neopixel_portal

![ESP8266](https://img.shields.io/badge/ESP8266-NodeMCU-black?style=for-the-badge&logo=espressif)
![Arduino IDE](https://img.shields.io/badge/Arduino_IDE-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Interface](https://img.shields.io/badge/UI-Captive_Portal-orange?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)
![Author](https://img.shields.io/badge/Author-Abdelrahman--Elnahrawy-blue?style=for-the-badge)

## 📖 Overview
The **esp8266_mqtt_neopixel_portal** is a professional-grade IoT node controller. It eliminates the need to hard-code WiFi credentials by providing a **Web-based Configuration Portal**. If the device cannot find a known network, it creates its own Hotspot, allowing users to submit WiFi and MQTT Broker details directly from a smartphone browser.

## 🚀 Key Features
* **🏠 Captive Portal:** Custom-styled HTML/CSS interface for easy network provisioning.
* **💾 Persistent Storage:** Saves SSID, Password, and MQTT Broker IP to **EEPROM** to survive power cycles.
* **📡 MQTT Integration:** Real-time bi-directional communication for IR data and system status.
* **🌈 NeoPixel Ready:** Pre-configured for WS2812B LED strips with standard animation functions.
* **🛡️ Connection Recovery:** Sophisticated loop logic to auto-reconnect WiFi/MQTT or failover to AP mode.

## 🛠️ Hardware Setup
| Component | Pin | Label |
| :--- | :--- | :--- |
| **NeoPixel Strip** | GPIO 14 | **D5** |
| **Status LED** | GPIO 2 | **D4** |



## ⚙️ How to Use
1. **Flash:** Upload the code via Arduino IDE.
2. **Setup:** On first boot, connect your phone to the WiFi network **"Unimote Setup"**.
3. **Configure:** Open `192.168.4.1` (or wait for the portal to pop up), enter your credentials, and click **Save**.
4. **Operate:** The device restarts, connects to your router, and begins MQTT communication.

## 👤 Author
* **Abdelrahman Elnahrawy**
* GitHub: [@Abdelrahman-Elnahrawy](https://github.com/Abdelrahman-Elnahrawy)

## ⚖️ License
This project is licensed under the **MIT License**.