# 🫁 Flow Balance Monitoring System – Arduino
نظام مراقبة توازن تدفّق الهواء – أردوينو

![Arduino](https://img.shields.io/badge/Platform-Arduino-blue)
![Language](https://img.shields.io/badge/Language-C%2FC%2B%2B-green)
![Status](https://img.shields.io/badge/Status-Prototype-orange)

---

## 📌 Overview | نظرة عامة

**English**  
This project monitors and validates the balance between **Oxygen Flow**, **Air Flow**, and **Patient Flow** using analog sensors connected to an Arduino.  
The system continuously checks whether the patient flow matches the combined air and oxygen flow within a ±5% tolerance.

**العربي**  
المشروع ده بيقوم بمراقبة والتحقق من توازن **تدفق الأكسجين** و**تدفق الهواء** و**تدفق المريض** باستخدام حساسات تناظرية متصلة بالأردوينو.  
النظام بيتأكد بشكل مستمر إن تدفق المريض يساوي مجموع تدفق الهواء + الأكسجين بنسبة سماحية ±5%.

---

## ⚙️ System Concept | فكرة النظام

```
Patient Flow ≈ Air Flow + Oxygen Flow
```

**English**  
If the patient flow deviates beyond ±5%, the system raises an error flag indicating abnormal operation.

**العربي**  
لو تدفق المريض خرج عن النطاق المسموح بيه (±5%)، النظام بيرفع إشارة خطأ تدل على وجود خلل.

---

## 🧩 Hardware Requirements | المتطلبات العتادية

| Component | المكوّن |
|---------|---------|
| Arduino Board | Arduino Uno / Mega / Compatible |
| Oxygen Flow Sensor | حساس تدفق الأكسجين |
| Air Flow Sensor | حساس تدفق الهواء |
| Patient Flow Sensor | حساس تدفق المريض |
| USB / Serial Monitor | كابل USB + شاشة تسلسلية |

---

## 🔌 Sensor Connections | توصيل الحساسات

| Signal | Arduino Pin |
|------|-------------|
| Oxygen Flow | A5 |
| Air Flow | A6 |
| Patient Flow | A7 |

---

## 🧠 Software Logic | منطق البرنامج

### 1️⃣ Sampling & Averaging | أخذ العينات والمتوسط
- Each sensor is read **10 times**
- Readings are averaged to reduce noise and ADC jitter  
- كل حساس يتم قراءته **10 مرات**
- يتم حساب المتوسط لتقليل التشويش وعدم استقرار الـ ADC

---

### 2️⃣ Flow Accumulation | تجميع التدفق
- Averaged values are accumulated over a **3-second window**  
- يتم تجميع المتوسطات خلال نافذة زمنية **3 ثواني**

---

### 3️⃣ Flow Balance Validation | التحقق من التوازن

```
Patient Flow ∉ (Air Flow + Oxygen Flow) ± 5%
→ ERROR FLAG SET
```

- If imbalance detected → `ERROR = 1`  
- عند وجود خلل يتم تفعيل إشارة الخطأ

---

## 🚨 Error Handling | معالجة الأخطاء

| Variable | Description |
|--------|------------|
| `ERROR` | 0 = Normal operation |
| `ERROR` | 1 = Flow imbalance detected |

---

## 📐 Flow Conversion Equation | معادلة تحويل التدفق

⚠ **WARNING / تحذير**

**English**  
This linear equation is **NOT medically validated** and is used for **testing purposes only**.

**العربي**  
المعادلة التالية **غير معايرة طبيًا** ومستخدمة **للاختبار فقط**.

```cpp
Flow = (AverageReading - 68) * 0.265 + 2.7;
```

> Etnafis Team is **NOT responsible** for any damage caused by using this equation.

---

## 🛠️ Features | المميزات

- Noise-reduced analog readings  
- Real-time flow consistency checking  
- 3-second rolling validation window  
- Simple and expandable architecture  

- تقليل التشويش في قراءات الحساسات  
- مراقبة التوازن في الوقت الحقيقي  
- نافذة تحقق زمنية 3 ثواني  
- تصميم بسيط وقابل للتطوير  

---

## 🧪 Project Status | حالة المشروع

**Prototype / Experimental**  
For research and testing purposes only.

**نموذج أولي / تجريبي**  
لأغراض البحث والاختبار فقط.

---

## 🏷️ Tags

```
arduino
embedded-systems
flow-sensor
medical-device-prototype
oxygen-flow
air-flow
patient-monitoring
signal-processing
adc
iot
```

---

## 📄 License
This project is provided **as-is** for educational and research purposes.
