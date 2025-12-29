# 🫁 Arduino_LCD_Ventilator_UI_Pressure_Volume_Display
واجهة عرض LCD لنظام جهاز تنفّس صناعي باستخدام Arduino لعرض الضغط، الأكسجين، معدل التنفس، الحجم، ونسبة I/E

Author: Abdelrahman Elnahrawy  
License: MIT

![Arduino](https://img.shields.io/badge/Platform-Arduino-blue)
![LCD](https://img.shields.io/badge/Display-16x4_LCD-green)
![Status](https://img.shields.io/badge/Status-Prototype-orange)

---

## 📌 Overview | نظرة عامة

**English**  
This project implements a 16x4 LCD user interface for a ventilator-like system using Arduino.  
It displays real-time parameters such as pressure, oxygen percentage, respiratory rate, volume, ventilation mode, and I/E ratio.  
An error state can override the display to show a critical alarm message.

**العربي**  
المشروع عبارة عن واجهة عرض باستخدام شاشة LCD 16x4 مع Arduino،  
لإظهار بيانات جهاز شبيه بجهاز التنفّس الصناعي مثل:  
الضغط، نسبة الأكسجين، معدل التنفس، الحجم، وضع التشغيل، ونسبة الشهيق/الزفير.  
في حالة الخطأ، يتم عرض رسالة تحذير قوية على الشاشة.

---

## ⚙️ Features | المميزات

- LCD 16x4 interface using LiquidCrystal library  
- Displays multiple ventilation parameters simultaneously  
- Supports multiple ventilation modes (Pressure / Volume)  
- Error handling mode with alarm message  
- Simple and readable UI layout  

---

## 🧩 Hardware Requirements | المتطلبات العتادية

| Component | المكوّن |
|---------|---------|
| Arduino Board | Arduino Uno / Nano |
| LCD Display | 16x4 LCD (HD44780) |
| Potentiometer | لضبط التباين (V0) |
| Wires | أسلاك توصيل |

---

## 🔌 Pin Connections | توصيل الشاشة

| LCD Pin | Arduino Pin |
|-------|-------------|
| RS | 12 |
| EN | 11 |
| D4 | 5 |
| D5 | 4 |
| D6 | 3 |
| D7 | 2 |
| RW | GND |
| VSS | GND |
| VDD | +5V |
| V0 | Potentiometer |

---

## 🧠 Software Logic | منطق البرنامج

1. Initialize LCD in 16x4 mode  
2. Print static labels once during startup  
3. Update dynamic values (pressure, oxygen, rate, volume) in loop  
4. Display current ventilation mode and I/E ratio  
5. If an error occurs, override display with alarm message  

--
🏷️ Tags
Arduino
LCD
Ventilator
Medical-UI
Pressure-Control
Volume-Control
Embedded-Systems
Human-Machine-Interface
Prototype

📄 License
MIT License – Provided by Abdelrahman Elnahrawy for educational and research purpose
