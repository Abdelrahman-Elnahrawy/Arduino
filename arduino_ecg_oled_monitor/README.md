# 🩺 arduino_ecg_oled_monitor

![Arduino](https://img.shields.io/badge/Arduino-Uno%2FNano-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Arduino IDE](https://img.shields.io/badge/Arduino_IDE-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![OLED](https://img.shields.io/badge/Display-SH1106_OLED-blueviolet?style=for-the-badge)
![Medical](https://img.shields.io/badge/Field-Medical_Lab_Instrumentation-red?style=for-the-badge)

## 📖 Overview
The **arduino_ecg_oled_monitor** is a specialized medical lab project developed for the **HNU 2nd Year Medical Lab Cohort**. It serves as a real-time visualization platform for Electrocardiogram (ECG) signals. 

The system captures weak electrical heart signals (simulated or via an AD8232 sensor), processes the data through a scrolling buffer, and renders a high-fidelity waveform on a 1.3" SH1106 OLED display. Additionally, it features a synchronous buzzer "beep" for pulse detection and Bluetooth data streaming for remote monitoring.



## 🚀 Advanced Features
* **📈 Dynamic Waveform Rendering:** Implements a scrolling buffer that creates a smooth "oscilloscope" effect on the OLED.
* **🔊 Synchronous Bio-Feedback:** A digital buzzer provides audible confirmation of high-amplitude peaks (QRS complexes).
* **📱 Wireless Telemetry:** Streams live ECG coordinates via Bluetooth (HC-05/HC-06) for integration with mobile apps or PC serial plotters.
* **🎨 Custom UI Design:** Features a dedicated header and a splash screen representing the HNU Medical Lab academic cohort.

## 🛠️ Hardware Specifications
| Component | Pin (Arduino) | Description |
| :--- | :--- | :--- |
| **ECG Module (e.g. AD8232)** | A0 | Analog input for cardiac signal |
| **OLED (SH1106)** | I2C (A4/A5) | 128x64 high-contrast display |
| **Buzzer** | D8 | Piezoelectric alarm for heart rate |
| **Bluetooth HC-05** | D10 (RX), D11 (TX) | Serial data transmission |



## ⚙️ How it Works
1. **Signal Mapping:** The 10-bit Analog-to-Digital Converter (ADC) reads values (0-1023). These are mathematically mapped to the vertical pixel height of the OLED display area.
2. **Buffer Management:** A rolling array of 128 integers stores the signal history. Every new reading shifts the previous 127 values to the left, creating the moving animation.
3. **Interrupt-Safe Drawing:** Utilizing the `U8g2` library's "Page Buffer" mode to ensure low RAM consumption on ATmega328P chips while maintaining flicker-free updates.

## 📦 Required Libraries
Download these via the Arduino Library Manager:
* **U8g2:** High-performance display driver.
* **SoftwareSerial:** Enables Bluetooth communication on digital pins.
* **Wire:** Required for I2C OLED communication.

## 👤 Author
* **Abdelrahman Elnahrawy**
* GitHub: [@Abdelrahman-Elnahrawy](https://github.com/Abdelrahman-Elnahrawy)

## ⚖️ License
This project is licensed under the **MIT License**.