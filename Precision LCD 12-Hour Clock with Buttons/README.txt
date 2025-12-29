# ⏰ Arduino Precision LCD Clock

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
