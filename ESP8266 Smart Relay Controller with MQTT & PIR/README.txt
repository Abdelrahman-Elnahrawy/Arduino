# 🌐 ESP8266 Smart Relay Controller with MQTT & PIR

This Arduino/ESP8266 sketch implements a **smart relay control system** with analog buttons, PIR sensor input, and MQTT connectivity.

## 🖥️ Features
- Controls **6 relays** (R1–R6) via **analog button input** or MQTT commands.  
- Supports **short press toggles** and analog-range detection for multiple buttons.  
- **PIR motion sensor** integration for automatic relay control.  
- **MQTT communication**: publish relay status and receive remote commands.  
- **Mode switching** with relaymod output for special operations.  
- Adjustable **timers, delays, and thresholds**.

## ⚙️ Hardware Connections
- Relays:  
  - Relay1 → D6 (R1)  
  - Relay2 → D7 (R2)  
  - Relay3 → D5 (R3)  
  - Relay4 → D8 (R4)  
  - Relay5 → D3 (R5)  
  - Relay6 → D0 (PWM, R6)  
- Mode relay → D2 (relaymod)  
- PIR sensor → D4 (pir)  
- Analog buttons → A0  

## 🌐 WiFi & MQTT
- WiFi SSID / Password: `"Na7rawy Limited" / "Selim&Nahrawy751"`  
- MQTT Broker: `192.168.1.123`  
- MQTT Username / Password: `"zabolaa"`  
- MQTT Topics:  
  - Publish: `"pub"`  
  - Subscribe: `"sub"`  

## ⏱️ Behavior
1. **Button Presses**:  
   - Short/long presses mapped to relays R1–R6.  
   - Button analog ranges trigger different relays.  
2. **PIR Sensor**:  
   - Motion can toggle R1 automatically depending on mode.  
3. **MQTT Commands**:  
   - Relay control via messages.  
   - Status updates published every 500ms.  
4. **Relay6 PWM Control**:  
   - Adjusted by analog input or MQTT message.  
5. **Mode Operation**:  
   - relaymod pin triggers special timed operations.

## 🎯 Use Case
Ideal for **home automation**, **remote relay control**, or **smart sensor-based devices** where relays, motion detection, and MQTT-based remote control are required.
