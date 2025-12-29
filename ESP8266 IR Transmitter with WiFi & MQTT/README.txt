# 🌐 ESP8266 IR Transmitter with WiFi & MQTT

This Arduino/ESP8266 sketch allows the ESP8266 to **transmit IR signals**, **connect to WiFi**, and **communicate via MQTT**, with a built-in web configuration portal for WiFi credentials.

## 🖥️ Features
- Transmit **IR signals** using the `IRsend` library.  
- Connect to a **WiFi network** or create an **Access Point** if WiFi fails.  
- Communicate IR commands over **MQTT** (`PubSubClient`).  
- **EEPROM storage** for WiFi SSID and password, persisting across reboots.  
- Web interface to **configure WiFi credentials** at `http://<ESP_IP>/`.

## ⚙️ Hardware Connections
- **IR LED** → Pin D4 (GPIO4)  
- ESP8266 module (any variant)  

> Optional: On-board LED can be used for debugging.

## 🔌 Behavior
1. Attempts to connect to stored WiFi credentials.  
2. If WiFi fails within 7 seconds → starts **AP mode** with a configuration portal.  
3. Connects to MQTT broker if WiFi is connected.  
4. Receives IR raw data via MQTT and transmits it through the IR LED.  
5. Stores new WiFi credentials in EEPROM via web portal and **restarts ESP**.

## 📡 MQTT
- Broker: `MQTT_BROKER_IP`  
- Port: 1883  
- Topic: `IR_RAW_DATA_TOPIC`  
- Authentication supported (`MQTT_USERNAME` / `MQTT_PASSWORD`)  

## 🎯 Use Case
Ideal for creating a **WiFi + MQTT controlled IR remote**, such as for TVs, air conditioners, or other IR-controlled devices, with easy WiFi configuration for users.
