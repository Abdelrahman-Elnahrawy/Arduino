# ⚡ ESP8266 Interrupt Handler

![ESP8266](https://img.shields.io/badge/ESP8266-NodeMCU-black?style=for-the-badge&logo=espressif)
![Arduino IDE](https://img.shields.io/badge/Arduino_IDE-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Type](https://img.shields.io/badge/Logic-Hardware_Interrupts-red?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)
![Author](https://img.shields.io/badge/Author-Abdelrahman--Elnahrawy-orange?style=for-the-badge)

## 📖 Overview
The **ESP8266_Interrupt_Handler** is a technical demonstration of using **Hardware Interrupts** on the ESP8266 platform. Interrupts allow the microcontroller to pause its current execution immediately when a specific external event occurs (like a button press or sensor trigger), ensuring zero-latency response.

This is significantly more efficient than "polling" (checking a pin state in a loop) because it frees up the CPU to handle other tasks, like maintaining a WiFi connection.

## 🚀 Key Features
* **⏱️ Instant Response:** Captures high-speed signals that occur between loop cycles.
* **🔋 Power Efficiency:** Allows the CPU to sleep or handle complex tasks until an event occurs.
* **🛡️ Debounce Handling:** Implements software-based timing to prevent multiple triggers from mechanical noise.
* **🔄 ISR Logic:** Uses a clean `ICACHE_RAM_ATTR` designated Interrupt Service Routine (ISR).

## 🛠️ Hardware Requirements
* **Microcontroller:** ESP8266 (NodeMCU / Wemos D1 Mini).
* **Input Device:** Push Button or Digital Sensor (PIR, Hall Effect, etc.).
* **Indicator:** Built-in LED (GPIO 2).

## 🔌 Pin Configuration
| Component | ESP8266 Pin | Note |
| :--- | :--- | :--- |
| **Trigger Input** | GPIO 12 (D6) | Supports Interrupts |
| **Onboard LED** | GPIO 2 (D4) | Visual Feedback |



## ⚙️ How it Works
1.  **Attach:** The code uses `attachInterrupt(digitalPinToInterrupt(pin), ISR, RISING)` in the `setup()`.
2.  **Trigger:** When the pin voltage changes from LOW to HIGH, the hardware pauses the main loop.
3.  **Execute:** The `handleInterrupt()` function runs immediately to update a state or toggle an LED.
4.  **Resume:** The main loop continues exactly where it left off.

## 👤 Author
* **Abdelrahman Elnahrawy**
* GitHub: [@Abdelrahman-Elnahrawy](https://github.com/Abdelrahman-Elnahrawy)

## ⚖️ License
This project is licensed under the **MIT License**.