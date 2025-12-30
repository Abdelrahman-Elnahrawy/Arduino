# ESP8266 MQTT IR Raw Transmitter

Control IR devices remotely using **ESP8266**, **MQTT**, and an **IR LED**.  
The ESP8266 listens to MQTT messages and transmits **raw IR data** to control devices like TVs, ACs, and more.

## Preview
![ESP8266](https://raw.githubusercontent.com/github/explore/main/topics/esp8266/esp8266.png)
![MQTT](https://raw.githubusercontent.com/github/explore/main/topics/mqtt/mqtt.png)
![IR Remote](https://upload.wikimedia.org/wikipedia/commons/5/56/IR_remote_control.jpg)

## Features
- MQTT to IR bridge
- Raw IR transmission
- WiFi-based remote control
- Compatible with Home Assistant
- Lightweight and fast

## Hardware
- ESP8266 (NodeMCU / ESP-12)
- IR LED
- 220Ω resistor
- External power (recommended)

## Wiring
| Component | ESP8266 |
|--------|--------|
| IR LED | GPIO1 |
| GND | GND |

## Required Libraries
- IRremoteESP8266
- ESP8266WiFi
- PubSubClient

## MQTT Topic
IR_RAW_DATA_TOPIC

markdown
Copy code

## How It Works
1. ESP8266 connects to WiFi
2. Connects to MQTT broker
3. Subscribes to IR topic
4. Receives raw IR data
5. Transmits IR signal via LED

## Use Cases
- Smart IR blaster
- AC / TV control
- Home automation
- MQTT to IR gateway

## Tags
esp8266  
mqtt  
infrared  
iot  
homeautomation  

## Provided By
**Abdelrahman Selim**  
## License
MIT