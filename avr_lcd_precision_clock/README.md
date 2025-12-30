# avr_lcd_precision_clock_backlight_timeout

![Platform](https://img.shields.io/badge/Platform-Arduino_AVR-blue?style=for-the-badge)
![UI](https://img.shields.io/badge/Interface-LCD_16x2-green?style=for-the-badge)
![Power](https://img.shields.io/badge/Feature-Auto_Backlight_Sleep-orange?style=for-the-badge)

## 📖 Overview
The **avr_lcd_precision_clock_backlight_timeout** is a standalone digital clock firmware that provides high-accuracy timekeeping using the ATmega’s internal `millis()` counter. It features an intelligent power-saving mode that disables the LCD backlight after a period of inactivity and a responsive 200ms polling loop for manual time adjustment.

---

## 🚀 Key Features

* **⏱️ Software RTC Logic:** Uses a non-blocking `millis()` subtraction method to maintain time accuracy, avoiding the drift associated with standard `delay()` calls.
* **🌙 Auto-Dimming Backlight:** Features a 30-second timeout (configurable) to save power and extend the life of the LCD's LED backlight.
* **🔘 Responsive UI:** The 1-second main cycle is divided into five 200ms sub-cycles, allowing the device to detect button presses for setting hours and minutes with minimal latency.
* **🖥️ Dynamic Contrast Control:** Contrast ($V_O$) is managed via a PWM signal on Pin 9, eliminating the need for a physical potentiometer.

---

## 🛠️ Hardware Architecture

### Pin Mapping
| Component | Pin | Type | Function |
| :--- | :--- | :--- | :--- |
| **LCD RS** | GPIO 2 | Digital | Register Select |
| **LCD Enable**| GPIO 3 | Digital | Enable Signal |
| **LCD D4-D7** | 4, 5, 6, 7 | Digital | Data Bus |
| **Contrast** | GPIO 9 | **PWM** | PWM-based Contrast ($V_O$) |
| **Backlight** | GPIO 10 | **PWM** | Backlight Control |
| **Hour Set** | GPIO 0 | Input | Hours Increment (Pull-up) |
| **Minute Set**| GPIO 1 | Input | Minutes Increment (Pull-up) |



---

## 🎮 Operation Instructions

1. **Setting Time:** Press the button connected to Pin 0 to increment Hours. Press the button on Pin 1 to increment Minutes (this also resets Seconds to zero).
2. **Backlight Wake:** If the screen is dark, pressing either button will wake the backlight without changing the time.
3. **AM/PM Logic:** The clock operates in 12-hour format and automatically toggles the AM/PM flag when the hour passes 12.

---

## 👤 Author
* **Abdelrahman Elnahrawy**
* **Project Identity:** `avr_lcd_precision_clock_backlight_timeout`# ⏰ Arduino Precision LCD Clock

This Arduino sketch implements a **12-hour digital clock** using a 16x2 LCD and two buttons to set the time.  

## 🖥️ Features
- Displays **Hours : Minutes : Seconds** with **AM/PM** indicator.
- Real-time updates without using `delay()`, ensuring **better timing accuracy**.
- **Backlight control** with automatic timeout.
- **Time set buttons** for adjusting hours and minutes.
- Handles **seconds, minutes, hours, and AM/PM overflow** automatically.

## 🔧 Hardware Connections
- LCD pins:  
  - RS → 2  
  - EN → 3  
  - D4 → 4  
  - D5 → 5  
  - D6 → 6  
  - D7 → 7  
- LCD contrast PWM → 9  
- Backlight PWM → 10 (adjust current to <7mA)  
- Time set buttons:  
  - Hours → A0 (pin 0)  
  - Minutes → A1 (pin 1)  

## ⏱️ Time Set Buttons
- **Button 1:** Increase hours 🔼  
- **Button 2:** Increase minutes 🔼  
- Pressing any button **resets the backlight timeout**.

## 💡 Backlight
- Turns off automatically after a timeout (default 150 x 200ms cycles ≈ 30s).  
- Pressing any button **reactivates backlight** immediately.

## ⚙️ Time Accuracy
- Uses `millis()` instead of `delay()` to ensure accurate seconds counting.  
- Updates LCD every 200ms for faster button response and smoother operation.

## 🎯 Use Case
Ideal for projects requiring a **simple, precise 12-hour clock** with easy adjustment buttons and backlight control.
