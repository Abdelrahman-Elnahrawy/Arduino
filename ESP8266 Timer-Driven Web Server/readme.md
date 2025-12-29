# ⏱️ ESP8266 Timer-Driven Web Server

![ESP8266](https://img.shields.io/badge/ESP8266-Server-black?style=for-the-badge&logo=espressif)
![Arduino IDE](https://img.shields.io/badge/Arduino_IDE-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Language](https://img.shields.io/badge/Web-HTML%2FJS-orange?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)
![Author](https://img.shields.io/badge/Author-Abdelrahman--Elnahrawy-orange?style=for-the-badge)

## 📖 Overview
This project demonstrates a high-performance **Web Server** hosted on the ESP8266 that utilizes **Hardware Timers** (via the `Ticker` library or `os_timer`) instead of the standard `delay()` function. 

This approach ensures that the web server remains highly responsive and "non-blocking." While the ESP8266 manages the web interface, it simultaneously executes background tasks (like sensor polling or LED blinking) at precise intervals.

## 🚀 Key Features
* **⚡ Non-Blocking Architecture:** Background tasks run on interrupts, so the web server never "freezes."
* **📊 Real-Time Updates:** Uses AJAX or WebSockets to update the web page data without requiring a full page refresh.
* **📱 Responsive UI:** A clean, mobile-friendly HTML interface served directly from the ESP8266 Flash memory.
* **🔧 Precision Timing:** High-resolution timers for tasks that require exact intervals (e.g., telemetry every 10 seconds).

## 🛠️ Hardware Requirements
* **Microcontroller:** ESP8266 (NodeMCU v1.0 / Wemos D1 Mini).
* **Network:** Any 2.4GHz WiFi Access Point.
* **Optional:** Sensors (DHT11/DHT22 or DS18B20) to display data on the dashboard.

## 💻 Software Components
1. **ESP8266WebServer:** Handles the HTTP requests and routing.
2. **Ticker Library:** Manages the hardware-level timing for periodic tasks.
3. **SPIFFS/LittleFS (Optional):** Used if the HTML/CSS/JS files are stored separately from the `.ino` sketch.

## 🔌 Connection Diagram


## 🚀 Getting Started
1. **Configuration:** Open the sketch and enter your WiFi `SSID` and `Password`.
2. **Upload:** Use the **Arduino IDE** to flash the code to your ESP8266.
3. **Access:** * Open the Serial Monitor (115200 Baud) to find the local IP address assigned to the board.
   * Type the IP address (e.g., `192.168.1.50`) into any web browser.
4. **Interact:** Use the buttons on the web interface to toggle GPIOs or view live data updates.

## 👤 Author
* **Abdelrahman Elnahrawy**
* GitHub: [@Abdelrahman-Elnahrawy](https://github.com/Abdelrahman-Elnahrawy)

## ⚖️ License
This project is licensed under the **MIT License**.
