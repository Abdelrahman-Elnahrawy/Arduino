# ESP8266 MQTT NeoPixel Multi LED Controller

Control multiple NeoPixel LEDs remotely using MQTT over WiFi with ESP8266.

![Arduino IDE](https://raw.githubusercontent.com/github/explore/main/topics/arduino/arduino.png)
![ESP8266](https://raw.githubusercontent.com/github/explore/main/topics/esp8266/esp8266.png)
![MQTT](https://raw.githubusercontent.com/github/explore/main/topics/mqtt/mqtt.png)

---

## Features
- ESP8266 WiFi connectivity
- MQTT-based NeoPixel control
- Individual RGB control per LED
- Global brightness adjustment
- Real-time updates
- Arduino IDE compatible

---

## Hardware Requirements
- ESP8266 (NodeMCU / ESP-12 / ESP-01)
- WS2812B NeoPixel LED strip or ring
- External 5V power supply
- Common ground between ESP8266 and LEDs

> Important: Do NOT power NeoPixels from ESP8266 3.3V pin

---

## Required Libraries
Install using Arduino Library Manager:
- ESP8266WiFi
- Adafruit NeoPixel
- PubSubClient

---

## MQTT Topics

### Brightness Control
**Topic**
neopixel/brightness

markdown
Copy code
**Payload**
0 – 255

markdown
Copy code

### LED Color Control
**Topic**
neopixel/color/<LED_INDEX>

markdown
Copy code
**Payload**
R,G,B

yaml
Copy code

---

## Example MQTT Messages

Turn LED #3 Red:
Topic: neopixel/color/3
Payload: 255,0,0

vbnet
Copy code

Set brightness to 50%:
Topic: neopixel/brightness
Payload: 128

yaml
Copy code

---

## Arduino IDE Setup
1. Install ESP8266 Boards Package
2. Select your ESP8266 board
3. Install required libraries
4. Edit WiFi & MQTT credentials
5. Upload the sketch

---

## File Name
esp8266_mqtt_neopixel_multi_led_controller.ino

yaml
Copy code

---

## Tags
arduinoide  
esp8266  
mqtt  
neopixel  
ws2812b  
iot  
led  

---

## Provided By
**Abdelrahman Elnahrawy**  

---

## License
MIT License – Free to use, modify, and distribute.