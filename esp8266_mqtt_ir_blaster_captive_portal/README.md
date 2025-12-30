# esp8266_mqtt_ir_blaster_captive_portal

![Platform](https://img.shields.io/badge/Platform-ESP8266-blue?style=for-the-badge&logo=espressif)
![Protocol](https://img.shields.io/badge/Protocol-MQTT-green?style=for-the-badge&logo=mqtt)
![Feature](https://img.shields.io/badge/Interface-Captive_Portal-orange?style=for-the-badge)

## 📖 Overview
The **esp8266_mqtt_ir_blaster_captive_portal** (Internal Name: **Unimote**) is a universal remote gateway. It connects your legacy Infrared (IR) devices (TVs, ACs, Stereos) to your smart home via MQTT. It features a fail-safe provisioning system that allows you to configure WiFi credentials through a mobile browser if the connection is lost.

---

## 🚀 Key Features

* **📡 MQTT-to-IR Bridge:** Listens for raw IR data strings over a specified MQTT topic and fires them via an IR LED using the `IRremoteESP8266` library.
* **💾 Persistent Storage:** Stores WiFi SSID and Password in EEPROM to ensure automatic reconnection after power cycles.
* **🌐 Smart Fallback (AP Mode):** If the device cannot find the stored WiFi network or the MQTT broker within 7–10 seconds, it automatically creates a hotspot named **"Unimote Setup"** for configuration.
* **🛠️ Transistor-Driven IR:** Designed for high-power IR transmission (best used with a 2N2222 or similar transistor to drive the IR LED).

---

## 🛠️ Hardware Architecture

### Pin Assignment
| Component | Pin | Function |
| :--- | :--- | :--- |
| **IR LED** | GPIO 4 (D2) | Data transmission (38kHz Carrier) |
| **Status LED** | GPIO 2 (D4) | Built-in LED for connection feedback |



---

## 📡 Provisioning Flow
1. **First Boot:** Device enters Access Point (AP) mode.
2. **Connect:** Use a smartphone to connect to the "Unimote Setup" WiFi.
3. **Configure:** Open `192.168.4.1` in your browser.
4. **Operation:** Enter credentials; the device reboots and joins your network to listen for MQTT commands.

---

## 👤 Author
* **Abdelrahman Elnahrawy**
* **Project Identity:** `esp8266_mqtt_ir_blaster_captive_portal`