# ESP32 Brushless DC Motor Control with ESC (PWM & Blynk Integration)

This repository contains firmware implementations for controlling a **Brushless DC (BLDC) motor** via an **Electronic Speed Controller (ESC)** using an **ESP32 microcontroller**.  

Two versions are included:

1. **Basic PWM ESC Control** – local control using ESP32 LEDC PWM  
2. **Blynk IoT ESC Control** – remote control via **Blynk mobile app** (WiFi)

This project demonstrates **modular, professional embedded firmware structure**, including hardware abstraction, configuration headers, and documentation.

---

## Table of Contents

- [Features](#features)  
- [Hardware Requirements](#hardware-requirements)  
- [Wiring & Diagrams](#wiring)  
- [PWM Specifications](#pwm-specifications)  
- [Firmware Variants](#firmware-variants)  
- [Software Setup](#software-setup)  
- [PlatformIO Instructions](#platformio-instructions)  
- [Repository Structure](#repository-structure)   
- [Author](#author)  

---

## Features

### Basic PWM ESC Control
- Generates 50Hz PWM signal with 16-bit resolution  
- Smooth throttle ramp from **1 ms to 2 ms** pulse width  
- Built-in LED indicates maximum throttle  

### Blynk ESC Control
- Remote ESC throttle control via **Blynk app**  
- Real-time speed adjustment over WiFi  
- Modular code ready for **mobile app integration**  

---

## Hardware Requirements

| Component | Specification / Notes |
|-----------|----------------------|
| ESP32 Dev Module | Any ESP32 development board (WROOM / WROVER) |
| Electronic Speed Controller (ESC) | For brushless motors |
| Brushless DC Motor (BLDC) | Compatible with your ESC |
| Power Supply | For ESC and motor (do not power from ESP32) |
| Connecting wires | For signal and power connections |

---

## Wiring 

### Basic PWM Wiring

| ESC Pin | ESP32 Pin / Connection |
|---------|-----------------------|
| Signal  | GPIO 4 |
| GND     | ESP32 GND |
| VCC     | External Battery / ESC power |

**Optional LED Indicator:** GPIO 2 → Built-in LED`

> ⚠️ Always ensure **motor and ESC are powered externally**. Do not power motor from ESP32.

---

## PWM Specifications

| Parameter | Value |
|-----------|-------|
| PWM Frequency | 50 Hz (20 ms period) |
| PWM Resolution | 16-bit (65536 steps) |
| Minimum Pulse Width | 1 ms |
| Maximum Pulse Width | 2 ms |
| Increment Step | 1 duty cycle per 20 ms (smooth ramp) |

---

## Firmware Variants

### 1. Basic ESC Control
- Location: `firmware/basic_pwm_control/main.cpp`  
- Provides gradual throttle control using LEDC PWM

### 2. Blynk ESC Control
- Location: `firmware/blynk_control/main.cpp`  
- Future implementation for remote IoT control via Blynk app  
- Uses WiFi and Blynk libraries for control  

---

## Software Setup

1. Install [VS Code](https://code.visualstudio.com/)  
2. Install [PlatformIO IDE extension](https://platformio.org/platformio-ide)  
3. Clone this repository:

```bash
git clone https://github.com/tanzeel532/esp32_pwm_brushless_dc_motor_control.git
```

4. Open the folder in VS Code  
5. Install PlatformIO dependencies automatically when prompted  

---

## PlatformIO Instructions

- **Build and Upload Basic ESC Firmware:**

```bash
# Build
pio run -e esp32dev

# Upload to ESP32
pio run -e esp32dev --target upload
```

- **Switch to Blynk firmware**  
  Update `platformio.ini`:

```ini
[platformio]
src_dir = firmware/blynk_control

[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
lib_deps = blynkkk/Blynk
```

Then build and upload again.

---

## Repository Structure

```
esp32-esc-control
│
├── firmware/
│   ├── basic_pwm_control/   ← Current PWM ESC code
│   │   └── main.cpp
│   └── blynk_control/       ← Future Blynk code
│       └── main.cpp
├── docs/                    ← Wiring diagrams, schematics
│   └── esc_wiring_diagram.png
├── include/                 ← Header files if needed
├── lib/                     ← External libraries
├── src/                     ← Optional placeholder or config
│   └── config.h
├── test/                    ← Unit tests (optional)
├── platformio.ini            ← PlatformIO configuration
├── .gitignore
└── README.md
```

---  

## Author

**Muhammad Tanzeel**  
- Embedded Systems & IoT Developer  
- Portfolio-ready project for ESC control and IoT firmware