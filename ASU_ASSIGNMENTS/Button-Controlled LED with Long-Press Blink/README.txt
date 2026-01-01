# 🔘 Button-Controlled LED with Long-Press Blink

This Arduino sketch controls an LED using a single button with **short press and long press functionalities**.

## 🖥️ Features
- **Short Press (<3s):** Toggle LED ON/OFF.
- **Long Press (≥3s):** Enable/disable LED blinking mode.
- LED blinks at **400ms intervals** when blinking mode is active.

## ⚙️ Hardware Connections
- Button → Pin 2  
- LED → Pin 13  

> Note: Button is read as `LOW` when pressed (internal pull-up enabled).

## ⏱️ Behavior
1. Press the button briefly → LED toggles state (ON/OFF).  
2. Press and hold for more than 3 seconds → LED starts or stops blinking.  
3. LED blink interval = 400ms.  

## 🎯 Use Case
Useful for **learning button input handling**, **short vs long press detection**, and **basic LED control**.
