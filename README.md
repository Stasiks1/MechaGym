# MechaGym 🏋️‍♂️

Hands-on C++ embedded training ground and algorithmic sandbox for **M5StickC PLUS (ESP32)** development.

## 🎯 Overview

`MechaGym` is a dedicated laboratory repository designed for mastering low-level embedded C++ architecture from scratch without auto-generated templates: state machines, non-blocking asynchronous timing, random generator algorithms, and modular DRY rendering.

---

## 🚀 Workouts & Modules

### 🏎️ Workout #1: Speed & Transmission Dashboard Controller
A standalone powertrain simulation and digital vehicle dashboard:
- **State & Clamping Logic:** Real-time acceleration (`+= 10`) and braking (`-= 10`) constrained strictly to safety boundaries `[0, 100]`.
- **Automatic Transmission State Engine:**
  - `PARKED` (`speed == 0`) — Blue status indicator.
  - `DRIVE` (`speed > 0 && speed < 80`) — Green cruising indicator.
  - `OVERHEAT!` (`speed >= 80`) — Red danger threshold alarm.
- **Acoustic Feedback:** Frequency-differentiated tones via onboard buzzer (`M5.Beep`).
- **Modular DRY Architecture:** Centralized `updateDashboard()` rendering engine.

---

### ⏱️ Workout #2: Cowboy Duel / Millisecond Reaction Time Tester
An arcade-style reflex benchmarking game built on a non-blocking 3-State Machine (`switch-case`):

- **State Machine Lifecycle:**
  - `State 0 (IDLE)`: Blue start lobby awaiting player trigger.
  - `State 1 (WAITING)`: Red tension screen with pseudorandom countdown timer (`random(2000, 5000)` ms).
  - `State 2 (FIRE & BENCHMARK)`: Green flash trigger with acoustic burst, calculating microsecond-accurate player latency (`millis() - reactionStart`).
- **Anti-Cheat Penalty System:** Active false-start detection with instant penalty buzzer and screen lock.
- **Dynamic Performance Tiers:**
  - ⚡ **`CYBER GOD!`** — Latency `< 200 ms`
  - 🏎️ **`FAST REFLEX!`** — Latency `200 – 320 ms`
  - 🐢 **`TOO SLOW!`** — Latency `> 320 ms`

---

## 🎮 Controls

### Workout #1 (Speed Dashboard):
* **Button A (Front):** Throttle (`+10`, high-pitch beep).
* **Button B (Side):** Brake (`-10`, low-pitch beep).

### Workout #2 (Reaction Game):
* **Button A (Front):** Start Game / Fire Action / Restart.

---

## 🛠 Tech Stack
* **Language:** C++ (Embedded)
* **Platform:** ESP32 / PlatformIO / VS Code / Arduino Framework
* **Hardware:** M5StickC PLUS (ESP32-PICO, ST7789 Color LCD 135x240, Buzzer)
* **Concepts:** State Machines (`switch-case`), Non-blocking `millis()`, Pseudorandom Generators (`random()`), Boundary Clamping, Latency Benchmarking.

## 📄 License
MIT
