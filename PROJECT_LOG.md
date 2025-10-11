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
* **Lighting Logic:** Designed and logically implemented all major lighting features:
    * A "hold brake" model for realistic brake light operation.
        * Automatic headlights based on a photocell sensor threshold.
            * Automatic hazard lights linked to the 2-speed transmission channel.
                * High-load rock lights linked to an ACS712 current sensor.
                * **Output Control:** Integrated the FastLED library to control two separate addressable LED strips, providing a foundation for all animated lighting effects.
                * **Code Audit:** Performed a full audit of the resulting `v0.5` framework, correcting a minor initialization bug and confirming the overall logic is sound.

                **Status:** The software framework is feature-complete and ready for hardware testing and deployment.
### **October 10, 2025: Session 4 - Documentation Audit & Finalization**

**Summary:** Completed a full audit and update of all project documentation, including the Bill of Materials and hardware datasheets, to ensure all project assets are synchronized with the final design.

**Log Details:**
* **BOM Audit:** Compared the existing Bill of Materials (`.xlsx` file) against the `v0.5` code framework. Identified several obsolete and missing components.
* **BOM Update:** The master BOM was corrected by the user to reflect the current design (e.g., swapping P9823 for WS2812B LEDs, adding the photocell and its resistor). A `.csv` version was added to the repository for better accessibility.
* **Datasheets Added:** The official user manuals for the FS-R7P and FS-R7V receivers were downloaded and added to a new `docs` folder in the repository.
* **Git Workflow:** Established and confirmed the correct workflow for vendoring libraries by removing their `.git` history, ensuring the project is fully self-contained.

**Status:** The project is now in a "clean room" state. The code is complete, the documentation is accurate, and all assets are correctly version-controlled. The project is fully prepared for the hardware testing phase.
### **October 11, 2025: Session 6 - In-Depth Hardware Diagnostics & Root Cause Analysis**

**Summary:** Performed a comprehensive, hands-on diagnostic of the Flysky FS-R7P receiver. After extensive debugging of the software and development environment, the root cause of communication failure was identified as an inverted serial signal from the i-BUS port.

**Log Details:**
* **Local Environment Setup:** Successfully configured a native Windows development environment in VS Code with PlatformIO. All initial setup issues, including Git installation, COM port conflicts, and WSL environment problems, were resolved.
* **Diagnostic Debugging:** Worked through a series of compiler errors and runtime issues with multiple i-BUS libraries. This process ruled out library incompatibility, clock speed mismatches, and baud rate errors as the primary problem.
* **Hardware Verified:** Physical tests confirmed the receiver has a solid power connection and is correctly bound to the transmitter. The Arduino Nano Every is also fully functional.
* **Root Cause Identified:** The consistent "all zeros" data output, despite a successful software compile and valid hardware connection, definitively points to a signal-level issue. The i-BUS protocol's inverted serial signal is incompatible with the Arduino Nano Every's default hardware serial port logic.
* **Solution Defined:** The final, correct solution is to implement a simple NPN transistor-based hardware circuit to physically invert the signal before it reaches the Arduino's RX pin. A final diagnostic sketch (`v4.0`) was created for use with this hardware solution.

**Status:** The project is paused pending the construction of the hardware signal inverter. The diagnostic phase is complete, and the path forward is clear.