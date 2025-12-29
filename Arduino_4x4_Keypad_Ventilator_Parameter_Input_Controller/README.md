# ⌨️ Arduino_4x4_Keypad_Ventilator_Parameter_Input_Controller
نظام إدخال إعدادات جهاز تنفس صناعي باستخدام لوحة مفاتيح 4x4 على Arduino

**Author:** Abdelrahman Elnahrawy  
**License:** MIT

![Platform](https://img.shields.io/badge/Platform-Arduino-blue)
![MCU](https://img.shields.io/badge/MCU-ATmega328-green)
![Input](https://img.shields.io/badge/Input-4x4_Keypad-orange)
![Status](https://img.shields.io/badge/Status-Prototype-yellow)

---

## 📌 Overview | نظرة عامة

**English**  
This project implements a numeric input controller for a ventilator system using a 4x4 matrix keypad.  
It allows the user to configure critical ventilation parameters in a structured and time-safe manner.

**العربي**  
المشروع ده بيستخدم لوحة مفاتيح 4×4 لإدخال إعدادات جهاز تنفس صناعي بطريقة منظمة وآمنة زمنيًا بدون استخدام `delay()`.

---

## ⚙️ Features | المميزات

- 4x4 Matrix Keypad input
- Non-blocking input handling using `millis()`
- Parameter selection using dedicated keys
- Automatic value timeout (input reset after inactivity)
- Safe range clamping for medical parameters
- Serial monitoring for debugging

---

## 🧠 Controlled Parameters | الإعدادات المتحكم بها

| Parameter | Description | Range |
|---------|------------|-------|
| Oxygen (%) | Oxygen concentration | 21 – 100 |
| MP | Maximum pressure | 10 – 37 |
| Rate | Breathing rate (BPM) | 10 – 30 |
| Volume | Tidal volume (ml) | 270 – 800 |
| Mode | Ventilation mode | 1 – 4 |
| I/E Ratio | Inspiration/Expiration | 1 – 3 |

---

## 🔢 Keypad Control Logic | منطق التحكم بالكيبـاد

| Key | Function |
|----|----------|
| `1` | Edit Oxygen |
| `2` | Edit Pressure (MP) |
| `3` | Edit Rate |
| `4` | Edit Volume |
| `*` | Change Mode |
| `#` | Change I/E Ratio |

- Digits are entered sequentially
- Input auto-resets after 1.5 seconds of inactivity
- Values are clamped to safe operating ranges

---

## 🔌 Hardware Requirements | المتطلبات العتادية

| Component | Description |
|---------|------------|
| Arduino Uno / Nano | Main controller |
| 4x4 Matrix Keypad | User input |
| Serial Monitor | Debug output |

---

## 🧩 Pin Connections | توصيل الكيباد

| Keypad Pin | Arduino Pin |
|-----------|-------------|
| Row 1 | D9 |
| Row 2 | D8 |
| Row 3 | D7 |
| Row 4 | D6 |
| Col 1 | D5 |
| Col 2 | D4 |
| Col 3 | D3 |
| Col 4 | D2 |

---

## 🧠 Software Architecture | هيكلة البرنامج

1. Read keypad input
2. Select parameter based on control key
3. Accumulate numeric digits
4. Apply validation and limits
5. Reset input after timeout
6. Output values via Serial Monitor

---

## 🏷️ Tags

Arduino  
Arduino-IDE  
Keypad  
4x4-Keypad  
Embedded-Systems  
Medical-Devices  
Ventilator  
Human-Machine-Interface  
Non-Blocking-Code  
millis  

---

## 📄 License
MIT License  
© Abdelrahman Elnahrawy  
For educational and research purposes only.
