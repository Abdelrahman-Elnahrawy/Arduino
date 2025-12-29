# 🎛️ Analog Button Reader with Toggle and Increment

This Arduino sketch reads analog values from pin **A0** and maps them to six different virtual "buttons" or actions:

- **R1 to R5** are boolean flags that toggle their state (true/false) whenever the analog value falls within specific ranges.  
- **R6** is an integer counter that increases by 10 whenever the analog value is between 900 and 1020.  

The program checks the input every **1 second** ⏱️ to prevent multiple triggers from a single press.  

## 🔢 Analog Ranges and Actions
- `0 - 100` → Toggle **R1** 🔄  
- `201 - 299` → Toggle **R2** 🔄  
- `401 - 499` → Toggle **R3** 🔄  
- `601 - 699` → Toggle **R4** 🔄  
- `701 - 799` → Toggle **R5** 🔄  
- `900 - 1020` → Increment **R6** by 10 ➕  

## 💻 Output
The current values of all flags (`R1` to `R5`) and the counter `R6` are printed to the **Serial Monitor** for monitoring.

## 🎯 Use Case
Useful for reading multiple buttons or sensors through a **single analog input** (e.g., using a resistor ladder), and keeping track of toggles and counts.
