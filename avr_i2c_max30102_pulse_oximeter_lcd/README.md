# avr_i2c_max30102_pulse_oximeter_lcd

![Platform](https://img.shields.io/badge/Platform-Arduino_AVR-blue?style=for-the-badge)
![Sensor](https://img.shields.io/badge/Sensor-MAX30102-red?style=for-the-badge)
![Protocol](https://img.shields.io/badge/Protocol-I2C-orange?style=for-the-badge)

## 📖 Overview
The **avr_i2c_max30102_pulse_oximeter_lcd** is a non-invasive biometric monitoring system. It utilizes the MAX30102 high-sensitivity pulse oximeter and heart-rate sensor to acquire photoplethysmogram (PPG) data. The firmware processes IR and Red LED reflections to calculate Heart Rate (BPM) and Blood Oxygen Saturation (SpO2), displaying the results on a 16x2 I2C LCD.

---

## 🚀 Key Features

* **🩺 Real-Time Biometrics:** Continuous monitoring of BPM and SpO2 levels.
* **🛡️ Finger Detection Logic:** Implements an IR threshold check to distinguish between actual skin contact and ambient noise, ensuring the display remains clear when the sensor is idle.
* **⚡ High-Speed I2C:** Configured for `I2C_SPEED_FAST` (400kHz) to ensure high-frequency sampling of the PPG signal.
* **📉 Optimized Signal Processing:** Uses sample averaging (4 samples) and a 100Hz sample rate to filter out high-frequency noise and motion artifacts.

---

## 🛠️ Hardware Architecture

### Pin Assignment (I2C Shared Bus)
Both the LCD and the MAX30102 sensor share the I2C bus pins.

| Component | Arduino Pin | Function |
| :--- | :--- | :--- |
| **SDA** | A4 | Data Line |
| **SCL** | A5 | Clock Line |
| **VCC** | 5V / 3.3V | Power (Sensor requires 3.3V) |
| **GND** | GND | Common Ground |



---

## 📊 Sensor Configuration
The firmware configures the MAX30102 with the following stable parameters:
* **LED Brightness:** 6.2mA (Balances signal strength and power consumption).
* **ADC Range:** 4096 (12-bit resolution).
* **Pulse Width:** 411µs (Standard for high-accuracy SpO2 calculation).

---

## 👤 Author
* **Abdelrahman Elnahrawy**
* **Project Identity:** `avr_i2c_max30102_pulse_oximeter_lcd`