# Arduino Projects Collection

![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Arduino IDE](https://img.shields.io/badge/Arduino_IDE-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)
![Author](https://img.shields.io/badge/Author-Abdelrahman--Elnahrawy-orange?style=for-the-badge)

## Overview
A curated set of Arduino sketches and embedded modules covering sensors, displays, motor control, user interfaces, and connectivity. Each project follows consistent naming and code style, emphasizes non-blocking design where possible, and documents hardware wiring and dependencies.

Highlights include:
- OLED and LCD user interfaces (U8g2, I2C 16x2/20x4).
- Pulse-oximetry demos using MAX30102 (SparkFun MAX30105 library).
- HC-05 Bluetooth telemetry and serial bridges.
- Stepper motion control with Timer2 pulse generation and rotary encoder feedback via pin change interrupts.

## Repository Structure
- One project per folder. The primary sketch filename matches the folder name.
- New/renamed projects use snake_case for Arduino-safe names.
- Projects may contain supporting modules split into `.h`/`.cpp` files.
- Documentation: each project has a README.md with wiring, dependencies, and usage.


## Libraries / Dependencies
Install via Arduino Library Manager unless noted:
- U8g2 by olikraus (OLED SH1106/SSD1306)
- LiquidCrystal_I2C by Frank de Brabander (or compatible)
- SparkFun MAX3010x (MAX30105) by SparkFun Electronics
- PinChangeInterrupt (pin-change ISRs for A/B/Z encoders)
- Wire (built-in)
- SoftwareSerial (built-in)

Project READMEs list exact libraries used and wiring diagrams.

## Build and Upload
1. Open the project folder and `.ino` in Arduino IDE.
2. Select the correct Board (e.g., Arduino Uno/Nano) and Port.
3. Install required libraries from Library Manager.
4. Verify and Upload.

## Style Guide
- 2-space indentation, spaces around operators.
- Functions grouped by responsibility, with short comment headers.
- Avoid delay() in main logic; use `millis()` scheduling where possible.
- Parameterize magic numbers with named constants.

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
