# Arduino Radar Scanner (Ultrasonic + Servo + SH1106 OLED)

This project implements a real-time radar-style scanner using:

* **Arduino**
* **Ultrasonic Sensor (HC-SR04)**
* **Servo Motor**
* **1.3 inch SH1106 OLED Display** (128x64)

The servo sweeps from 0° to 180° and back, while the ultrasonic sensor measures distance. Detected points within a 30 cm range are plotted on the OLED display with a fading effect to simulate traditional radar visuals.

---

## 🚀 Features

* Smooth 0° → 180° → 0° sweeping motion
* Ultrasonic distance detection up to **30 cm**
* Real-time radar visualization on SH1106 OLED
* Fading effect for previously detected points
* Triple-circle radar UI
* Animated scan beam tail

---

## 📦 Hardware Requirements

* Arduino Uno / Nano
* HC-SR04 Ultrasonic Sensor
* SG90 Servo Motor
* 1.3" SH1106 OLED (I2C)
* Jumper wires
* Breadboard

---

## 🔌 Wiring Diagram

### **Ultrasonic Sensor (HC-SR04)**

| HC-SR04 | Arduino |
| ------- | ------- |
| VCC     | 5V      |
| GND     | GND     |
| TRIG    | D8      |
| ECHO    | D9      |

### **Servo Motor**

| Servo  | Arduino |
| ------ | ------- |
| Signal | D6      |
| VCC    | 5V      |
| GND    | GND     |

### **SH1106 OLED**

| OLED | Arduino |
| ---- | ------- |
| VCC  | 5V      |
| GND  | GND     |
| SCK  | A5      |
| SDA  | A4      |

---

## 📁 Project File Structure

```
├── radar_mini.ino     # Arduino code
├── README.md          # Project documentation
```

---

## 🛠️ Libraries Required

Install the following from the Arduino Library Manager:

* **Adafruit GFX Library**
* **Adafruit SH110X Library**
* **Servo.h** (built-in)

---

## ▶️ How It Works

1. The servo rotates across the scanning area.
2. At each angle, the ultrasonic sensor measures distance.
3. If a target is detected (≤ 30 cm), its position is converted to a coordinate on the OLED.
4. The point fades over several frames, creating a radar echo effect.
5. The OLED draws:

   * Three radar circles
   * A moving scan beam
   * Fading echo points

---

## 📸 Demo Output

![lv_0_20251121232911](https://github.com/user-attachments/assets/1ed9724d-1b98-47ac-970e-d87812a74a6e)


## 📜 License

This project is open-source under the MIT License.

---

## 🤝 Contributions

Pull requests are welcome! Feel free to improve the UI, add noise filtering, or optimize the scanning algorithm.
