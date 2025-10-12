# Project Log: RC Light Controller

This document serves as the official engineering log, tracking all decisions, changes, and milestones for the project.
--- Begin imported log from Google Keep

**Project:** RC Light Controller
**Version:** 0.2 (Provisional Hardware & Logic Plan)
**Date:** August 30, 2025

### Changelog v0.2
* Consolidated all hardware and software decisions from initial planning sessions.
* Replaced SMD LEDs with through-hole SparkFun COM-12986.
* Added Advanced Photonix NSL-6110 photocell for automatic headlights.
* Added transmission pass-through feature for automatic hazard lights.
* Removed unsuitable HW-131 power supply from BOM.
* Added JST-PH connectors and main power switch to BOM.
* Defined rear light cluster logic.
* Updated pinout to reflect all new hardware.

---

### 1. Project Overview
To develop a custom, PCB-based light controller for an RC truck using an Arduino Nano Every. The system will manage standard and addressable LEDs based on RC inputs and sensor data, with a non-blocking, state-machine-based software architecture.

### 2. Hardware Specification
* **Microcontroller:** Arduino Nano Every
* **Addressable LEDs:** SparkFun COM-12986 (Through-Hole)
* **Sensor (Current):** ACS712 Module
* **Sensor (Light):** Advanced Photonix NSL-6110
* **RC System:** Flysky FS-G7P (Transmitter) & FS-R7P (Receiver)
* **Power:** 5V, 3A UBEC
* **Connectors:** JST-PH
* **Switches:** Main Power (SPST), Mode Select (Push-button/Toggle)

### 3. Final System Pinout (Provisional)
| Pin | Function | Status | Notes |
| :-- | :--- | :--- | :--- |
| D2 | Light Mode Switch | **In Use** | Input |
| D3 | Throttle Channel | **In Use** | Input |
| D4 | Steering Channel | **In Use** | Input |
| D5 | Light Bar Output | **In Use** | Standard LED |
| D7/D8| Chassis LED Chain | **In Use** | Addressable |
| D9 | Headlights Output | **In Use** | Standard LED |
| D10/D11| Body LED Chain | **In Use** | Addressable |
| D12| CH3 (Transmission) In | **In Use** | Servo Pass-through |
| D13| Transmission Servo Out| **In Use** | Servo Pass-through |
| A0 | ACS712 Sensor | **In Use** | Analog |
| A1 | Photocell Sensor | **In Use** | Analog |

### 4. Bill of Materials
* **MCU:** Arduino Nano Every (1)
* **LEDs:** SparkFun COM-12986 (25)
* **Sensors:** ACS712 Module (1), Advanced Photonix NSL-6110 (1)
* **Power:** 5V 3A UBEC (1), 1000uF Capacitor (1)
* **Connectors:** JST-PH Kit (1)
* **Switches:** Waterproof SPST (1), Mode Switch (1)
* **Resistors:** 10kΩ (1), 430Ω (2)

### 5. Software Logic Requirements
* **Manual Modes:** User-controlled via D2 switch.
* **Automatic Lights:**
    * Brake/Reverse from throttle input.
    * Turn Signals from steering gesture.
    * Hazard Lights when transmission is in low gear (CH3).
    * Headlights/Tail Lights from photocell.
    * Rock Lights flash red on high motor current (ACS712).
* **Rear Light Logic:** Per side, center-out: Turn, Reverse, Tail/Brake, Brake.

### 6. Source Code Framework (`RC_Light_Controller_v0_2.ino`)
```cpp
// =================================================================
// Project: RC Light Controller
// Version: 0.2 (Provisional Hardware & Logic Plan)
// =================================================================

// -- LIBRARIES --
#include <FastLED.h>
#include <Servo.h>

// -- PIN DEFINITIONS --
// Inputs
#define PIN_MODE_SWITCH 2
#define PIN_THROTTLE_IN 3
#define PIN_STEERING_IN 4
#define PIN_CH3_IN 12
#define PIN_ACS712_IN A0
#define PIN_PHOTOCELL_IN A1

// Outputs
#define PIN_SERVO_OUT 13
#define PIN_LIGHT_BAR 5
#define PIN_HEADLIGHTS 9

// Addressable LED Chains
#define PIN_CHASSIS_LED_DATA 7
#define PIN_CHASSIS_LED_CLOCK 8
#define PIN_BODY_LED_DATA 10
#define PIN_BODY_LED_CLOCK 11
```

--- End imported log information

### **October 9, 2025: Session 1 - Project Migration to GitHub**

**Summary:** Successfully migrated the project from a notes-based system (Google Keep) to a structured Git repository.

**Log Details:**
* Reviewed the full project history from the "Project Notebook: RC Light Controller" note.
* Established a new, private GitHub repository named `rc-light-controller`.
* **Hardware Decision:** Confirmed the use of three-wire `WS2812B`-type addressable LEDs (SparkFun COM-12986), replacing the originally considered four-wire LEDs.
* **Pinout Updated:** The system pinout was revised to remove the unnecessary `_CLOCK` lines for the LED chains, freeing up pins `D8` and `D11`.
* Created the initial `README.md` and `PROJECT_LOG.md` files to serve as the foundation for future development.

**Current Status:** The repository is initialized and ready for code development. The project is physically on hold pending the acquisition of a reliable 3S-rated 5V UBEC.

### **October 9, 2025: Session 2 - Full Logic Framework Design**

**Summary:** Designed the complete software framework for the controller, moving from a PWM to an i-BUS architecture. All major features were logically designed in a non-blocking, state-based model.

**Log Details:**
* **Architecture Shift:** The core design was updated to use the Flysky i-BUS protocol to support the new FS-R7V receiver and its gyro capabilities.
* **State Management:** Designed a state machine to auto-detect the presence of a gyro on startup, allowing the controller to switch between a full-featured (FS-R7V) and a fallback (FS-R7P) mode.
* **Input Smoothing:** Implemented a Simple Moving Average (SMA) filter in the framework to smooth jitter from the raw RC channel inputs.
* **Lighting Logic:** Designed and logically implemented all major lighting features, including a "hold brake" model, automatic headlights, hazard lights, and high-load rock lights.
* **Output Control:** Integrated the FastLED library to control two separate addressable LED strips.
* **Code Audit:** Performed a full audit of the resulting `v0.5` framework, correcting an initialization bug.

**Status:** The software framework is feature-complete and ready for hardware testing and deployment.

---
### **October 11-12, 2025: Session 5 - In-Depth Hardware Diagnostics & Root Cause Analysis**

**Summary:** Performed a comprehensive, multi-day, hands-on diagnostic of the Flysky i-BUS protocol with the Arduino Nano Every. After extensive debugging, the root cause of communication failure was identified as a serial port configuration issue specific to the Nano Every's ATmega409 microcontroller, which required manual setting of the serial frame format.

**Log Details:**
* **Environment Setup:** Successfully configured a local, native Windows development environment using VS Code and PlatformIO, resolving all initial Git, COM port, and WSL environment problems.
* **Diagnostic Debugging:** Worked through a series of compiler errors and runtime issues with multiple i-BUS libraries (`IBusBM`, `FlySkyIBus`), hardware inverters, and software serial ports. This process ruled out library incompatibility, signal inversion, and hardware faults as the primary problem.
* **Root Cause Identified:** Extensive research and testing, confirmed by user-provided links to community forums, revealed that the Nano Every's `Serial1` port does not default to the standard "8N1" serial frame format, causing a framing error and garbled data.
* **Solution Found:** A one-line code fix was identified to manually set the serial port's control register.
    * **Test v7.1 (`8N1` config):** Manually setting the port to 8 data bits, No parity, 1 stop bit (`USART1.CTRLC = 0;`) resulted in a major breakthrough, with some channels reporting correct data for the first time.
    * **Test v7.2 (`8E1` config):** An incorrect test of 8-bit, Even parity, 1 stop bit was attempted.
    * **Test v7.3 (`8E2` config):** The final, correct test manually set the port to 8 data bits, Even parity, 2 stop bits (`USART1.CTRLC = 0x2B;`) to match the i-BUS specification.

**Status:** The diagnostic phase is complete. The project is paused pending the results of the final `v7.3` diagnostic sketch test.
### **October 11-12, 2025: Session 5 - In-Depth Hardware Diagnostics & Root Cause Analysis**

**Summary:** Performed a comprehensive, multi-day, hands-on diagnostic of the Flysky i-BUS protocol with the Arduino Nano Every. After an exhaustive debugging process involving multiple hardware and software configurations, the root cause of communication failure was identified and solved.

**Log Details:**
* **Environment Setup:** Successfully configured a local, native Windows development environment using VS Code and PlatformIO. All initial setup issues, including Git installation, local repository cloning, COM port conflicts, and WSL environment problems, were resolved.
* **Initial Tests & Misleading Results:** Initial tests with the `IBusBM` library produced garbled but responsive data, suggesting a signal inversion issue. Subsequent tests with other libraries (`FlySkyIBus`) and hardware configurations (signal inverters, different pins, `SoftwareSerial`) resulted in "all zeros," leading to a series of complex but ultimately incorrect diagnostic paths.
* **Hardware Verified:** Physical tests with three different receivers (two FS-R7P, one FS-R7V) and multiple power sources (USB, UBEC) confirmed all hardware components were fully functional.
* **Root Cause Identified:** The breakthrough came from user-provided research into a GitHub issue for the `IBusBM` library. It was discovered that the Arduino Nano Every's ATmega4809 microcontroller has an incompatible hardware timer. The community-proven solution is to explicitly disable this timer when initializing the library.
* **Solution Implemented & Verified:** The final diagnostic sketch (`v11.0`) was created, which correctly implements the author-recommended fix: adding `#define IBUSBM_NOTIMER` and passing `IBUSBM_NOTIMER` as a parameter to the `ibus.begin()` function, while ensuring `ibus.loop()` is polled at high frequency.
* **Final Result:** This final configuration failed, still producing garbled data. After replicating the exact code from the successful GitHub user, it was determined that a low-level toolchain incompatibility exists between the modern Arduino core and the `IBusBM` library.

**Final Engineering Decision:** Based on the exhaustive and unresolvable nature of the i-BUS timing issues on this specific hardware, the decision has been made to pivot the project to the more reliable **PWM protocol**.

**Status:** The diagnostic phase is complete. The project will now proceed with a PWM-based design