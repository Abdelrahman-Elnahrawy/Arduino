# 🧪 esp8266_multi_gas_kalman_monitor

![Filtering](https://img.shields.io/badge/Algorithm-Kalman_Filter-blueviolet?style=for-the-badge)
![Sensors](https://img.shields.io/badge/Sensors-MQ2_MQ5_MQ9-blue?style=for-the-badge)
![MQTT](https://img.shields.io/badge/Connectivity-MQTT-orange?style=for-the-badge)

## 📖 Overview
The **Environmental Monitoring Station** is an advanced air-quality analysis tool. Analog gas sensors are notorious for "signal noise" and fluctuating readings. This project solves that problem by implementing a **Simple Kalman Filter** in software, providing a steady and reliable data stream for safety-critical applications.



## 🚀 Key Features
* **📉 Noise Reduction:** The Kalman Filter algorithm predicts the next state based on previous readings, effectively ignoring random spikes in gas sensor data.
* **🌬️ Comprehensive Detection:** Monitors LPG, Methane, Carbon Monoxide (CO), Hydrogen, and Smoke simultaneously.
* **🌡️ Precise Temperature:** Uses the LM35 precision integrated-circuit temperature sensor.
* **☁️ MQTT Integration:** Streams filtered data to a broker for visualization in tools like Node-RED or Home Assistant.

## 🛠️ Hardware Architecture


### Sensor Configuration
| Sensor | Primary Target | Pin |
| :--- | :--- | :--- |
| **MQ-2** | LPG / Smoke | GPIO 34 |
| **MQ-5** | Natural Gas | GPIO 35 |
| **MQ-9** | Carbon Monoxide | GPIO 36 |
| **LM35** | Temperature | GPIO 39 |

**Note:** If using a standard ESP8266 (which has only 1 Analog pin), an external I2C ADC like the **ADS1115** is required to read all four sensors.

## ⚙️ Mathematical Logic
The system converts analog voltage to PPM (Parts Per Million) using characteristic curves.
$$V_{out} = \frac{ADC_{val} \times V_{ref}}{ADC_{res}}$$
The temperature is calculated linearly for the LM35:
$$Temp(^{\circ}C) = \frac{V_{out} \times 100}{1V}$$

## 👤 Author
* **Abdelrahman Elnahrawy**
* GitHub: [@Abdelrahman-Elnahrawy](https://github.com/Abdelrahman-Elnahrawy)

## ⚖️ License
This project is licensed under the **MIT License**.