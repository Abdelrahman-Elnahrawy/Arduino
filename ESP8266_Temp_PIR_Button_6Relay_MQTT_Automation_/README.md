# 🌡️ ESP8266_Temp_PIR_Button_6Relay_MQTT_Automation
نظام أتمتة منزلية ESP8266 مع قياس درجة الحرارة، كشف الحركة، زر ضغط، و 6 ريليه باستخدام MQTT

**Author:** Abdelrahman Elnahrawy  
**License:** MIT

![ESP8266](https://img.shields.io/badge/Platform-ESP8266-blue)
![Language](https://img.shields.io/badge/Language-C%2FC%2B%2B-green)
![Status](https://img.shields.io/badge/Status-Prototype-orange)

---

## 📌 Overview | نظرة عامة

**English**  
This project uses an ESP8266 microcontroller to:  
- Measure temperature using a DS18B20 sensor  
- Detect motion via PIR sensor  
- Detect push button presses  
- Control 6 relays via MQTT  
- Publish temperature, PIR alerts, button presses, and relay status periodically  

**العربي**  
المشروع يستخدم ESP8266 لعمل التالي:  
- قياس درجة الحرارة باستخدام حساس DS18B20  
- اكتشاف الحركة عبر حساس PIR  
- اكتشاف ضغط زر  
- التحكم في 6 ريليه عن طريق MQTT  
- نشر درجة الحرارة والتنبيهات وحالة الأزرار والريليه بشكل دوري  

---

## ⚙️ Features | المميزات

- Non-blocking timing using `millis()`  
- WiFi connection to MQTT broker (e.g., test.mosquitto.org)  
- Relay control through subscribed MQTT topic `"zabolaa"`  
- Debug messages via Serial Monitor  

---

## 🧩 Hardware Requirements | المتطلبات العتادية

| Component | المكوّن |
|---------|---------|
| ESP8266 Board | NodeMCU / Wemos D1 mini |
| DS18B20 Temperature Sensor | حساس درجة الحرارة DS18B20 |
| PIR Motion Sensor | حساس الحركة PIR |
| Push Button | زر ضغط |
| 6 Relays | 6 ريليه للتحكم بالأجهزة |
| Resistors & Wires | مقاومات وأسلاك توصيل |
| MQTT Broker | بروكر MQTT (مثال: test.mosquitto.org) |

---

## 🔌 Pin Connections | توصيل الحساسات و الريليه

| Device | ESP8266 Pin |
|--------|-------------|
| DS18B20 | D1 (GPIO5) |
| PIR Sensor | D4 (GPIO2) |
| Button | D2 (GPIO4) |
| Relay 1 | D6 (GPIO12) |
| Relay 2 | D7 (GPIO13) |
| Relay 3 | D5 (GPIO14) |
| Relay 4 | D8 (GPIO15) |
| Relay 5 | D3 (GPIO0) |
| Relay 6 | D0 (GPIO16) |

---

## 🧠 Software Logic | منطق البرنامج

1. Connect ESP8266 to WiFi and MQTT broker  
2. Subscribe to topic `"zabolaa"` to receive relay commands  
3. Parse MQTT payload to turn relays ON/OFF  
4. Read temperature from DS18B20 every 2 seconds and publish to `"esp8266/TEMP"`  
5. Detect PIR motion every 1 second and publish to `"esp8266/PIR"`  
6. Detect button press every 0.7 seconds and publish to `"esp8266/BUTTON"`  
7. Publish relay status every 2 seconds to `"esp8266/feedback"`  

---

## 🏷️ Tags

ESP8266
MQTT
Home-Automation
IoT
DS18B20
PIR-Sensor
Relay-Control
NodeMCU
Wemos
Temperature-Monitoring
Wireless-IoT

---

## 📄 License
MIT License - provided by Abdelrahman Elnahrawy for educational and research purposes.