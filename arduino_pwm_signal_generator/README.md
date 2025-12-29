# 🌟 arduino_pwm_signal_generator

Arduino PWM Signal Generator 1Hz - 1MHz with adjustable duty cycle 0-100%, minimum on/off time 0.2µs.

**Author:** Abdelrahman Elnahrawy  
**License:** MIT

![Platform](https://img.shields.io/badge/Platform-Arduino-blue)
![Language](https://img.shields.io/badge/Language-C%2FC%2B%2B-green)
![IDE](https://img.shields.io/badge/IDE-ArduinoIDE-orange)
![Status](https://img.shields.io/badge/Status-Prototype-lightgrey)

---

## 📌 Overview | نظرة عامة

**English**  
This project uses an Arduino Nano/Uno to generate a PWM signal:
- Frequency: 1Hz to 1MHz  
- Duty cycle: 0% to 100%  
- Minimum on/off time: 0.2µs  
- Output: Pin D9  
- Control via Serial Monitor  

**العربي**  
المشروع يستخدم Arduino Nano/Uno لتوليد إشارة PWM:
- التردد: من 1Hz إلى 1MHz  
- دورة التشغيل: من 0% إلى 100%  
- الحد الأدنى للزمن HIGH/LOW: 0.2µs  
- المخرج: Pin D9  
- التحكم عن طريق Serial Monitor  

---

## ⚙️ Features | المميزات

- Adjustable frequency and duty cycle  
- Minimum on/off time protection  
- Real-time updates via Serial Monitor  
- Uses Timer1 library for precise PWM  

---

## 🧩 Hardware Requirements | المتطلبات

| Component | Description |
|-----------|------------|
| Arduino Nano/Uno | Microcontroller |
| USB Cable | Programming & Power |
| Serial Monitor | Input frequency & duty cycle |

---

## 🧠 Software Logic | منطق البرنامج

1. Arduino reads frequency from Serial Monitor  
2. Arduino reads duty cycle from Serial Monitor  
3. Calculates on/off times  
4. Checks minimum on/off constraints  
5. Updates PWM signal on pin D9 using Timer1  

---

## 🏷️ Tags

![ArduinoIDE](https://img.shields.io/badge/ArduinoIDE-orange)  
![Arduino](https://img.shields.io/badge/Arduino-blue)  
![PWM](https://img.shields.io/badge/PWM-lightgrey)  
![Timer1](https://img.shields.io/badge/Timer1-green)  
![Signal-Generator](https://img.shields.io/badge/Signal--Generator-red)  
![Microcontroller](https://img.shields.io/badge/Microcontroller-purple)  

---

## 📄 License

MIT License - provided by Abdelrahman Elnahrawy for educational and research purposes.
