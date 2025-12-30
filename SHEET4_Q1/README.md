# LM35_Temperature_Controlled_Fan

![Arduino](https://img.shields.io/badge/Platform-Arduino-orange)
![Sensor](https://img.shields.io/badge/Sensor-LM35-red)
![PWM](https://img.shields.io/badge/Control-PWM-blue)
![Language](https://img.shields.io/badge/Language-C%2B%2B-blue)
![License](https://img.shields.io/badge/License-MIT-green)
![Author](https://img.shields.io/badge/Author-Abdelrahman--Elnahrawy-orange)



## 📌 Project Overview (English)

This project was implemented as part of the **Introduction to Embedded Systems** course at **Ain Shams University**,  
**Sheet 4 – Question 1**.

The system uses an **LM35 temperature sensor** to measure ambient temperature and controls a **DC fan speed** using **PWM**.

### 🔹 System Behavior
- Temperature < **20°C** → Fan OFF
- Temperature between **20°C – 40°C** → Fan speed increases linearly
- Temperature > **40°C** → Fan OFF (safety limit)

---

## 📌 شرح المشروع (Arabic)

تم تنفيذ هذا المشروع ضمن مادة **Introduction to Embedded Systems**  
**جامعة عين شمس – Sheet 4 Question 1**

يعتمد النظام على حساس **LM35** لقياس درجة الحرارة، ويتم التحكم في سرعة مروحة DC باستخدام **PWM**.

### 🔹 آلية العمل
- أقل من **20 درجة مئوية** → المروحة متوقفة
- من **20 إلى 40 درجة مئوية** → زيادة سرعة المروحة تدريجيًا
- أعلى من **40 درجة مئوية** → إيقاف المروحة للحماية

---

## 🔧 Hardware Components

- Arduino Board
- LM35 Temperature Sensor
- DC Fan
- Transistor / Motor Driver
- External Power Supply (if needed)

---

## ⚙️ How It Works (English)

1. LM35 outputs 10mV per °C.
2. Arduino reads analog voltage.
3. Temperature is calculated in Celsius.
4. PWM signal controls fan speed proportionally.

---

## ⚙️ طريقة العمل (Arabic)

1. حساس LM35 يعطي 10 مللي فولت لكل درجة مئوية.
2. الأردوينو يقرأ الجهد عن طريق ADC.
3. يتم تحويل القراءة إلى درجة حرارة.
4. يتم التحكم في سرعة المروحة باستخدام PWM.

---

## 📜 License

This project is licensed under the **MIT License**.

---

## ✍️ Author

**Abdelrahman Elnahrawy**