# ⚡ Arduino AC Phase Control with Zero-Cross Detection

This Arduino sketch implements **zero-cross detection** and **AC phase control** using an optocoupler and DIAC. It allows controlling the power delivered to an AC load by adjusting the firing angle.

## 🖥️ Features
- **Zero-cross detection** on digital pin D8 (input from optocoupler)  
- **DIAC pulse output** on digital pin D3 to control AC power  
- **Analog input modulation**: potentiometer on A0 adjusts pulse delay  
- **Frequency measurement**: prints detected AC frequency every 500ms  
- **Interrupt-driven detection** for accurate timing  

## ⚙️ Hardware Connections
- **Optocoupler input** → D8 (detect AC zero-cross)  
- **DIAC pulse output** → D3 (phase control)  
- **Potentiometer** → A0 (adjust pulse delay)  
- Arduino board (ATmega328 or compatible)  

## ⏱️ Behavior
1. Detects **zero-cross events** from AC using interrupts  
2. Measures AC **frequency** and prints to Serial Monitor  
3. Generates a **DIAC pulse** after a delay based on the potentiometer  
4. Maps analog input (0–1024) to a delay of 10–7200 µs  
5. Frequency updates every 500ms and pulse delay is adjustable  

## 🎯 Use Cases
- AC **motor speed control**  
- **Light dimmers**  
- **Heating element controllers**  
- Projects that require **precise zero-cross detection** and **phase angle modulation**  

⚠️ **Warning:** This project involves **AC voltage**. Take all necessary safety precautions when connecting and testing.
