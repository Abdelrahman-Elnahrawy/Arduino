# 🎮 Arduino PS3 Controller Monitor

This Arduino sketch allows you to **monitor a PlayStation 3 controller** via Bluetooth using the `Ps3Controller` library. It prints **button presses, analog stick movements, and connection status** to the Serial Monitor.

## 🖥️ Features
- Detects **digital button events** (cross, circle, square, triangle, D-pad, triggers, shoulder buttons, sticks, start/select/PS button).  
- Detects **analog values** for sticks and buttons.  
- Shows **battery status** (charging, full, high, low, dying, shutdown).  
- Automatically **restarts Arduino/ESP** if controller is not connected after 10 seconds.  
- **Connection notifications** printed to Serial Monitor.

## ⚙️ Hardware Connections
- **Bluetooth adapter** (compatible with PS3 controllers).  
- Arduino board (any supported by `Ps3Controller` library).  

> No additional wiring required besides the Bluetooth adapter.

## ⏱️ Behavior
1. On startup, attempts to connect to a PS3 controller.  
2. Prints all **button presses/releases** and analog stick movements in real time.  
3. Restarts automatically if the controller is not connected within 10 seconds.  
4. Continuously monitors controller input in the loop.

## 🎯 Use Case
Ideal for **testing PS3 controller input**, **learning analog and digital button events**, and integrating a PS3 controller with Arduino-based projects such as **robotics, games, or custom interfaces**.
