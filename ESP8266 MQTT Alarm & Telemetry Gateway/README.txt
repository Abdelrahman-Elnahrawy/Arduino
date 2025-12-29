### 📛 Project Name

**ESP8266 MQTT Alarm & Telemetry Gateway**

---

### 📄 README-Style Description

This project turns an **ESP8266** into a **Wi-Fi–connected MQTT gateway** that publishes sensor/relay status, alarms, and telemetry data while also providing **local web configuration and EEPROM-based storage**.

The device connects to a Wi-Fi network, communicates with an **MQTT broker** using publish/subscribe topics, and periodically sends structured status messages containing multiple inputs (R1–R6), temperature, load/data values, and counters. Critical events trigger an **immediate alarm message** via MQTT.

---

### 🔧 Key Features

* **MQTT communication** using `PubSubClient`
* Periodic **telemetry publishing** (non-blocking using `millis()`)
* **Alarm reporting** via dedicated MQTT messages
* **EEPROM storage** for configuration and credentials
* Built-in **HTTP web server** for local setup/control
* **mDNS support** for easy device discovery on the network
* Static IP configuration for reliable local access

---

### 🧠 How It Works

* ESP8266 connects to Wi-Fi with predefined network settings
* Configuration data (user, password, IDs) is loaded from EEPROM
* MQTT client connects to the broker and subscribes to control topics
* Device continuously monitors inputs and system states
* Every fixed interval, a formatted telemetry string is published
* Alarm conditions immediately trigger an `"alarm"` MQTT message
* A local web server allows configuration and monitoring

---

### 🧩 Libraries Used

* `ESP8266WiFi.h`
* `PubSubClient.h`
* `EEPROM.h`
* `ESP8266WebServer.h`
* `ESP8266mDNS.h`

---

### 🎯 Typical Use Cases

* IoT alarm systems
* Remote monitoring & control panels
* Industrial or home automation nodes
* ESP8266 devices acting as **MQTT data collectors**

Send the **next code** whenever you’re ready — I’ll keep the same format and naming quality 👍
