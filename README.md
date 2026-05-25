#  Ultrasonic RGB Distance Indicator

> An Arduino project that uses an HC-SR04 ultrasonic sensor to measure distance and displays it visually using an RGB LED — green for far, yellow for medium, and red for close.

[![Arduino](https://img.shields.io/badge/Board-Arduino%20UNO%20R4%20Minima-00878F?logo=arduino&logoColor=white)](https://store.arduino.cc/products/uno-r4-minima)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![YouTube](https://img.shields.io/badge/Watch%20on-YouTube-FF0000?logo=youtube&logoColor=white)](https://www.youtube.com/@ARYANBUILDSS)

---

##  Watch the Build

> **Video coming soon on [ARYAN BUILDS](https://www.youtube.com/@ARYANBUILDSS)**  
> Subscribe so you don't miss it!

---

##  Demo

| Distance | LED Color | Range |
|---|---|---|
| Far | Green | > 30 cm |
| Medium | Yellow | 10 – 30 cm |
| Close | Red | < 10 cm |

---

##  Components

| Component | Quantity | Notes |
|---|---|---|
| Arduino UNO R4 Minima | 1 | Any Arduino Uno works too |
| HC-SR04 Ultrasonic Sensor | 1 | — |
| RGB LED (Common Anode) | 1 | Long leg → 5V |
| 220Ω Resistors | 3 | One per LED color channel |
| Breadboard | 1 | — |
| Jumper Wires | ~10 | Male-to-male |

---

## Wiring

```
HC-SR04 VCC   ──── 5V
HC-SR04 GND   ──── GND
HC-SR04 TRIG  ──── Pin 9
HC-SR04 ECHO  ──── Pin 10

RGB LED (+)   ──── 5V          ← long leg (common anode)
RGB LED R     ──── 220Ω ──── Pin 3
RGB LED G     ──── 220Ω ──── Pin 5
RGB LED B     ──── 220Ω ──── Pin 6
```

>  **Common Anode LED:** The long leg connects to **5V** (not GND). All color values are inverted in code using `255 - value`.

---

### Distance thresholds (easy to customize)

```cpp
#define CLOSE_DISTANCE  10   // cm — below this = RED
#define MID_DISTANCE    30   // cm — below this = YELLOW, above = GREEN
```

### How distance is calculated

```
distance (cm) = pulse duration (µs) / 58
```

Sound travels ~0.0343 cm per microsecond. Since the pulse travels *to* the object and *back*, we divide by 2, giving us the simplified formula above.

---

## 🚀 Getting Started

1. **Clone this repo**
   ```bash
   git clone https://github.com/speedcuber2424/code-for-the-ultrasonic-sensor-and-RGB-LED/blob/main/
   ```

2. **Open the sketch** in Arduino IDE  
   `File → Open → src/ultrasonic_rgb/ultrasonic_rgb.ino`

3. **Select your board**  
   `Tools → Board → Arduino UNO R4 Minima`  
   *(or whichever Arduino you're using)*

4. **Select your port**  
   `Tools → Port → COMx` (Windows) or `/dev/ttyUSBx` (Linux/Mac)

5. **Upload** and open Serial Monitor at **115200 baud**

---

## How It Works

1. The Arduino sends a 10µs HIGH pulse on the **TRIG** pin
2. The HC-SR04 fires 8 ultrasonic pulses at 40kHz
3. The echo bounces off the nearest object and returns to the **ECHO** pin
4. `pulseIn()` measures how long ECHO stays HIGH (in microseconds)
5. We divide by 58 to convert that time into centimeters
6. Based on the distance, `setColor()` lights up the RGB LED in the matching color

---

## Customization Ideas

- Change the `CLOSE_DISTANCE` and `MID_DISTANCE` values to suit your use case
- Add a buzzer that beeps faster as the object gets closer
- Replace the LED with a servo that sweeps based on distance
- Log readings to the Serial Plotter for a live graph (`Tools → Serial Plotter`)

---

## 🐛 Troubleshooting

| Problem | Likely Cause | Fix |
|---|---|---|
| LED stays off | Long leg not connected to 5V | Common anode long leg → 5V (not GND) |
| Wrong colors showing | R/G/B pins swapped | Test each pin with `setColor(255,0,0)` to identify |
| Distance always 0 | TRIG/ECHO swapped | TRIG → Pin 9, ECHO → Pin 10 |
| Huge distance readings (2000+ cm) | Loose ECHO wire | Push jumper wire firmly into breadboard |
| No Serial output | Wrong baud rate | Set Serial Monitor to **115200** |
| Board not detected | Charge-only USB cable | Use a data USB cable |

---

## License

This project is licensed under the [MIT License](LICENSE) — feel free to use, modify, and share it!

---

## Author

**Aryan** — [ARYAN BUILDS](https://www.youtube.com/@ARYANBUILDSS) 
---

*If this helped you, drop a ⭐ on the repo — it means a lot!*
