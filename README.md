# MechaGym 🏋️‍♂️

Hands-on C++ embedded training ground and algorithmic sandbox for **M5StickC PLUS (ESP32)** development.

## 🎯 Overview

`MechaGym` is a dedicated laboratory repository designed for mastering low-level embedded C++ architecture from scratch without auto-generated templates: state lifecycle management, boundary clamping, conditional logic, and modular (DRY) rendering engines.

---

## 🚀 Workouts & Modules

### 🏎️ Workout #1: Speed & Transmission Dashboard Controller
A standalone powertrain simulation and digital vehicle dashboard written entirely from scratch:

- **State & Clamping Logic:** Real-time acceleration (`+= 10`) and braking (`-= 10`) constrained strictly to safety boundaries `[0, 100]`.
- **Automatic Transmission State Engine:**
  - `PARKED` (`speed == 0`) — Blue status indicator.
  - `DRIVE` (`speed > 0 && speed < 80`) — Green cruising indicator.
  - `OVERHEAT!` (`speed >= 80`) — Red danger threshold alarm.
- **Acoustic Feedback:** Frequency-differentiated audio feedback via onboard buzzer (`M5.Beep` high-pitch tone on throttle vs. low-pitch tone on brake).
- **Modular DRY Architecture:** Centralized `updateDashboard()` function decoupling input processing from display rendering.

---

## 🎮 Controls

* **Button A (Front):** Accelerate (`+10`, high-pitch beep, max 100).
* **Button B (Side):** Brake (`-10`, low-pitch beep, min 0).

---

## 🛠 Tech Stack
* **Language:** C++ (Embedded)
* **Platform:** ESP32 / PlatformIO / VS Code
* **Hardware:** M5StickC PLUS (ESP32-PICO, ST7789 Color LCD 135x240, Buzzer)
* **Concepts:** Boundary Clamping, Boolean/Logical Operators (`&&`, `==`), DRY UI Architecture, Audio Frequency Generation.

## 📄 License
MIT
