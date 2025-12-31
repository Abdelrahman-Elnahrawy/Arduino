# ECG OLED + LCD + HC-05 Monitor (MAX30102)

![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Arduino IDE](https://img.shields.io/badge/Arduino_IDE-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Type](https://img.shields.io/badge/Display-OLED%20%2B%20LCD-lightgrey?style=for-the-badge)
![Sensor](https://img.shields.io/badge/Sensor-MAX30102-red?style=for-the-badge)
![Bluetooth](https://img.shields.io/badge/HC--05-Bluetooth-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)
![Author](https://img.shields.io/badge/Author-Abdelrahman--Elnahrawy-orange?style=for-the-badge)

## Overview
An Arduino-based monitor that:
- Draws an ECG-like waveform from analog input A0 on a 128x64 SH1106 OLED using U8g2.
- Shows numeric Pulse (BPM) and SpO2 (%) on a 16x2 I2C LCD.
- Streams values over Bluetooth via an HC-05 module.
- Samples a MAX30102 pulse-ox sensor (via SparkFun MAX30105 library) and computes simple estimates for BPM/SpO2.

This project is for demonstration and education. The BPM/SpO2 calculation is simplified and not medically accurate.

## Features
- Non-blocking scheduling using millis() for smooth UI and sampling.
- Page-buffered OLED drawing for consistent, flicker-free waveform.
- LCD value validation with "ERR" display for out-of-range readings.
- CSV telemetry over Bluetooth (e.g., `ECG:45%,SpO2:98%,BPM:76`).

## Hardware
- Board: Arduino Uno/Nano (ATmega328P)
- OLED: SH1106 128x64 (I2C)
- LCD: 16x2 I2C LCD (common addresses: 0x27 or 0x3F)
- Sensor: MAX30102 (I2C)
- Bluetooth: HC-05 (SoftwareSerial)
- Input: ECG analog signal on A0
- Output: Buzzer on D8 (optional)

### Wiring
- I2C (OLED + LCD + MAX30102):
  - SDA -> A4
  - SCL -> A5
- LCD backpack address: set in code (default 0x27). Change `LCD_I2C_ADDR` if needed (e.g., 0x3F/0x20).
- HC-05:
  - HC-05 TX -> Arduino D10 (SoftwareSerial RX)
  - Arduino D11 (SoftwareSerial TX) -> HC-05 RX (through voltage divider to 3.3V level recommended)
  - VCC -> 5V, GND -> GND
- Buzzer: D8 -> Buzzer (+), Buzzer (-) -> GND (use an active buzzer module if possible)
- ECG analog input: A0 -> ECG signal output (ensure a proper front end / isolation as needed)

## Libraries / Dependencies
Install via Arduino Library Manager unless noted:
- U8g2 by olikraus
- LiquidCrystal_I2C by Frank de Brabander (or compatible)
- SparkFun MAX3010x (MAX30105) by SparkFun Electronics
- Wire (built-in)
- SoftwareSerial (built-in)

## Build and Upload
1. Open `ecg_oled_lcd_bt_monitor.ino` in Arduino IDE.
2. Select your board and port.
3. Verify and Upload.

## Usage
- OLED shows a moving waveform derived from A0.
- LCD prints Pulse (BPM) and SpO2 (%), displaying "ERR" for out-of-range values.
- HC-05 publishes a CSV string once per second (default 9600 baud). Connect from a serial terminal on your phone/PC to observe values.

## Notes
- The MAX30102 BPM/SpO2 calculation here is intentionally simple for low resource usage and educational clarity.
- Adjust the LCD address constant `LCD_I2C_ADDR` if you see a blank LCD.
- Tune the ECG_ANALOG_MAX and buzzer threshold sections to fit your signal amplitude.

## License
MIT License

Copyright (c) 2025 Abdelrahman Elnahrawy

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

## Author
Abdelrahman Elnahrawy