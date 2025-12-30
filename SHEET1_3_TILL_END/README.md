# Introduction to Embedded Systems – ASU Assignments

![Platform: Arduino](https://img.shields.io/badge/Platform-Arduino-orange?style=for-the-badge&logo=arduino)
![Language: C/C++](https://img.shields.io/badge/Language-C%2B%2B-blue?style=for-the-badge)
![Embedded Systems](https://img.shields.io/badge/Field-Embedded_Systems-darkgreen?style=for-the-badge)
![PWM](https://img.shields.io/badge/Feature-PWM-yellow?style=for-the-badge)
![Serial](https://img.shields.io/badge/Interface-Serial_Communication-lightgrey?style=for-the-badge)
![Sensors](https://img.shields.io/badge/Sensor-LM35-red?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)
![Author](https://img.shields.io/badge/Author-Abdelrahman--Elnahrawy-orange?style=for-the-badge)

---

## 📘 Overview

This repository contains Arduino-based assignments developed for the  
**Introduction to Embedded Systems** course at **Ain Shams University (ASU)**.

The projects focus on **fundamental embedded concepts** such as:
- GPIO control
- Software & hardware PWM
- Serial communication
- Sensor interfacing
- Algorithmic problem solving

All code is written for **learning and academic purposes**.

---

## 📁 Project Files

### 1️⃣ `sheet_1_assignments.ino`

This file contains **multiple independent exercises** from **Sheet 1**.

> ⚠️ Each exercise is **commented out by default**  
> ✔️ Uncomment **only one section** at a time before uploading

#### Included Exercises

| Sheet | Title | Description |
|------|------|-------------|
| 1-1 | Idiot PWM | Software PWM using delays |
| 1-2 | Bouncing LEDs | LED chasing animation |
| 1-3 | Prime Numbers | Prime number detection logic |
| 1-4 | PWM via Serial | Serial-controlled pulse generation |
| 1-6 | Square Root | Serial-based square root calculator |
| 1-7 | Calculator | Sum, multiplication & average via text commands |

#### Covered Concepts
- Digital I/O
- Timing & delays
- Loops & conditions
- Serial parsing
- Floating-point math

---

### 2️⃣ `lm35_fan_controller.ino`

Assignment from **Sheet 4 – Question 1**

#### 🧠 Description
A **temperature-controlled fan system** using:
- **LM35 temperature sensor**
- **PWM fan speed control**

Fan speed changes **linearly** with temperature.

#### ⚙️ Control Logic

| Temperature | Fan Behavior |
|------------|-------------|
| < 20°C | OFF |
| 20°C – 40°C | PWM speed control |
| > 40°C | OFF (safety) |

#### Covered Concepts
- ADC (Analog-to-Digital Conversion)
- Sensor calibration
- PWM using `analogWrite()`
- Embedded control logic

---

## 🧰 Hardware Used
- Arduino Uno (or compatible)
- LEDs
- LM35 temperature sensor
- DC fan
- Basic resistors & wiring

---

## 🎓 Academic Context
- **Course:** Introduction to Embedded Systems  
- **University:** Ain Shams University (ASU)  
- **Type:** Laboratory / Sheet Assignments  

---

## 👤 Author
**Abdelrahman Elnahrawy**

---

## 📄 License

MIT License

Copyright (c) 2025 Abdelrahman Elnahrawy

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.

---

## 📝 Notes
- Code is intentionally **simple and direct**
- Some implementations are **not optimized** (academic requirement)
- Written to demonstrate **concept understanding**, not production use

---

⭐ If you find this helpful, feel free to fork or star the repository  
❤️ Thank you
