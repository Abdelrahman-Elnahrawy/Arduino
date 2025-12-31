# LCD Pulse/SpO2 Display Demo

![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Arduino IDE](https://img.shields.io/badge/Arduino_IDE-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Display](https://img.shields.io/badge/Display-16x2%20I2C%20LCD-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)
![Author](https://img.shields.io/badge/Author-Abdelrahman--Elnahrawy-orange?style=for-the-badge)

## Overview
Minimal LCD-only UI that displays Pulse (BPM) and SpO2 (%) on a 16x2 I2C LCD. It includes value validation and shows "ERR" when readings are out of range. The current sketch uses random demo values to exercise the UI; replace with your sensor reads for actual measurements.

## Features
- Clean, readable UI with labels and aligned numeric fields.
- 1 Hz display updates using millis() (non-blocking).
- Value validations with graceful error indicators.

## Hardware
- Board: Arduino Uno/Nano (ATmega328P)
- Display: 16x2 I2C LCD (PCF8574-based backpack)

### Wiring
- I2C:
  - SDA -> A4
  - SCL -> A5
- LCD address: change `LCD_I2C_ADDR` in code (common: 0x27 or 0x3F).

## Libraries / Dependencies
- LiquidCrystal_I2C (e.g., by Frank de Brabander)
- Wire (built-in)

## Build and Upload
1. Open `lcd_pulse_spo2_display_demo.ino` in Arduino IDE.
2. Select your board/port.
3. Verify and Upload.

## Usage
- The LCD displays Pulse and SpO2. In demo mode, values update every second and may show "ERR" to demonstrate validation.
- Integrate your sensor reads by assigning to `pulse_bpm` and `spo2_pct` instead of the random demo generation.

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