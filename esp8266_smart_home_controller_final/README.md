# 🏛️ ESP8266 6-Channel IoT Home Hub

![IoT](https://img.shields.io/badge/Tech-IoT_Home_Automation-blue?style=for-the-badge)
![Security](https://img.shields.io/badge/Feature-EEPROM_Recovery-red?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

## 📖 Overview
This project is a high-performance **Home Automation Controller** based on the ESP8266. It is designed to manage high-voltage appliances via a relay bank while providing intelligent automation using a PIR motion sensor. It communicates with any standard MQTT broker (configured by default for HiveMQ).



## 🚀 Key Features
* **📶 Captive Portal Provisioning:** If the system cannot find the stored WiFi, it creates an Access Point named "ESP help!!" where users can enter new credentials via a browser.
* **🔧 PWM Dimming:** The 6th channel (`relay6`) supports analog output, perfect for controlling DC motor speeds or LED strip brightness.
* **🧠 Three Operational Modes (LM):**
  - **Mode 1 (S):** Lights toggle instantly based on motion.
  - **Mode 2 (A):** Motion triggers light with a configurable "keep-on" delay (`LD`).
  - **Mode 3 (M):** Pure manual control via MQTT or physical buttons.
* **💾 Non-Volatile Memory:** All states (Relays, PWM levels, and Logic Modes) are saved to EEPROM, ensuring the home returns to its desired state after a power flicker.

## 🛠️ Hardware Setup
### Wiring Table


| Component | ESP8266 Pin | Description |
| :--- | :--- | :--- |
| **Relay 1-4** | D2, D1, D3, D4 | Standard AC Appliances |
| **Relay 5** | D8 | Extra Digital Load |
| **Relay 6** | D0 | PWM/Analog Load |
| **PIR Sensor** | RX (GPIO 3) | Motion Detection |
| **Keypad Buttons** | D5, D6, D7 | Local Manual Override |

## ⚙️ Communication Protocol
The device publishes its state every 500ms to the `ESP_Pub_1` topic in JSON-like string format:
`R1:0 R2:1 R3:0 ... T:750 #123`

## 👤 Author
* **Abdelrahman Elnahrawy**
* GitHub: [@Abdelrahman-Elnahrawy](https://github.com/Abdelrahman-Elnahrawy)