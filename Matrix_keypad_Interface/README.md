# ⌨️ HelloKeypad: Matrix Input Interface

![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Arduino IDE](https://img.shields.io/badge/Arduino_IDE-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Category](https://img.shields.io/badge/Category-User_Interface-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)
![Author](https://img.shields.io/badge/Author-Abdelrahman--Elnahrawy-orange?style=for-the-badge)

## 📖 Overview
The **HelloKeypad** project is a foundational implementation of a **Membrane Matrix Keypad** interface. It allows an Arduino to read inputs from a 4x4 (or 4x3) grid of buttons using only 8 pins (instead of 16), thanks to a row-column scanning technique.

This is the standard way to add numeric input, password entry, or menu navigation to your electronic projects.

## 🚀 Key Features
* **🧮 Matrix Scanning:** Efficiently reads multiple buttons using a minimal number of GPIO pins.
* **⌨️ Character Mapping:** Custom map to define what each key represents (0-9, A-D, *, #).
* **🔘 Debouncing Logic:** Built-in software handling to prevent "double-taps" or ghosting.
* **⚡ Event-Driven:** Designed to trigger actions the moment a key is pressed.

## 🛠️ Hardware Requirements
* **Microcontroller:** Arduino Uno / Nano / Mega.
* **Keypad:** 4x4 Matrix Membrane Keypad.
* **Jumper Wires:** For connecting the 8-pin header.

## 🔌 Pin Configuration (Standard 4x4)
| Keypad Pin | Arduino Pin | Function |
| :--- | :--- | :--- |
| **Pin 1** | D9 | Row 1 |
| **Pin 2** | D8 | Row 2 |
| **Pin 3** | D7 | Row 3 |
| **Pin 4** | D6 | Row 4 |
| **Pin 5** | D5 | Column 1 |
| **Pin 6** | D4 | Column 2 |
| **Pin 7** | D3 | Column 3 |
| **Pin 8** | D2 | Column 4 |



## ⚙️ How it Works
1. **The Grid:** The keypad is wired in rows and columns.
2. **The Scan:** The Arduino sets one row `LOW` at a time and checks the state of the columns.
3. **Detection:** If a column is detected as `LOW` while a specific row is active, the intersection identifies the exact key pressed.

## 📄 Usage
1. Connect the keypad to your Arduino following the pin table above.
2. Open the `.ino` file in the **Arduino IDE**.
3. Upload the code and open the **Serial Monitor**.
4. Press keys on the pad and watch the characters appear on your screen!

## 👤 Author
* **Abdelrahman Elnahrawy**
* GitHub: [@Abdelrahman-Elnahrawy](https://github.com/Abdelrahman-Elnahrawy)

## ⚖️ License
This project is licensed under the **MIT License**.