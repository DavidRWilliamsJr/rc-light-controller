# Project Log: RC Light Controller

This document serves as the official engineering log, tracking all decisions, changes, and milestones for the project.

---
## Imported Log from Google Keep

*Begin imported log from Google Keep*

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

### 1. Project Overview
The project is to develop a custom, PCB-based light controller for an RC truck using an Arduino Nano Every. The system will manage standard and addressable LEDs based on RC inputs and sensor data, with a non-blocking, state-machine-based software architecture.

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
| :--- | :--- | :--- | :--- |
| D2 | Light Mode Switch | **In Use** | Input |
| D3 | Throttle Channel | **In Use** | Input |
| D4 | Steering Channel | **In Use** | Input |
| D5 | Light Bar Output | **In Use** | Standard LED |
| D7/D8 | Chassis LED Chain | **In Use** | Addressable |
| D9 | Headlights Output | **In Use** | Standard LED |
| D10/D11 | Body LED Chain | **In Use** | Addressable |
| D12 | CH3 (Transmission) In | **In Use** | Servo Pass-through |
| D13 | Transmission Servo Out | **In Use** | Servo Pass-through |
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

---
*End imported log information*

---
## October 9, 2025: Session 1 - Project Migration to GitHub

**Summary:** Successfully migrated the project from a notes-based system (Google Keep) to a structured Git repository.

**Log Details:**
* Reviewed the full project history from the "Project Notebook: RC Light Controller" note.
* Established a new, private GitHub repository named `rc-light-controller`.
* **Hardware Decision:** Confirmed the use of three-wire `WS2812B`-type addressable LEDs (SparkFun COM-12986), replacing the originally considered four-wire LEDs.
* **Pinout Updated:** The system pinout was revised to remove the unnecessary `_CLOCK` lines for the LED chains, freeing up pins `D8` and `D11`.
* Created the initial `README.md` and `PROJECT_LOG.md` files to serve as the foundation for future development.

**Current Status:** The repository is initialized and ready for code development. The project is physically on hold pending the acquisition of a reliable 3S-rated 5V UBEC.

---
## October 9, 2025: Session 2 - Full Logic Framework Design

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
## October 10, 2025: Session 3 - Environment & Documentation Finalization

**Summary:** Configured the local development environment and finalized all project documentation and library dependencies, creating a fully self-contained project.

**Log Details:**
* **Environment Migration:** Transitioned the development workflow from a cloud-based GitHub Codespace to a native Windows environment running on the local machine. This was done to allow direct hardware access via the computer's USB ports.
* **Local Toolchain Setup:**
    * Installed Visual Studio Code locally.
    * Installed the PlatformIO IDE extension within VS Code.
    * Installed Git for Windows to enable version control from the local terminal.
* **Repository Cloning:** Cloned the `rc-light-controller` repository from GitHub to a local directory.
* **Library Vendoring:** All required project libraries (IBusBM, FastLED, VarSpeedServo, Streaming) were correctly cloned and "vendored" into the repository's `lib` folder. All submodule-related Git issues were debugged and corrected, resulting in a clean and portable project structure that no longer relies on external library installation.
* **Documentation:**
    * Created a `docs` folder to act as a central repository for project documentation.
    * Added hardware datasheets for the FS-R7P and FS-R7V receivers.
    * Added the project Bill of Materials (BOM) as an Excel file, and later as a `.csv` for better accessibility.
    * Established a `RESEARCH.md` file to log external links and key findings from our troubleshooting.

**Status:** The development environment is fully configured and all project assets are correctly version-controlled. The project is ready for hands-on hardware testing.

---
## October 11, 2025: Session 4 - Initial i-BUS Hardware Diagnostics

**Summary:** Began the hands-on hardware diagnostic phase for the Flysky i-BUS protocol on the Arduino Nano Every, encountering and working through the central technical challenge of the project.

**Log Details:**
* **Initial Test:** A diagnostic sketch (v1.2) using the IBusBM library was deployed to the hardware (Arduino Nano Every and FS-R7P receiver).
* **First Result:** The test resulted in garbled but responsive data (e.g., values in the 50,000 range instead of 1000-2000). This became the primary clue for the subsequent debugging effort.
* **Hypothesis 1 (Signal Inversion):** Based on common knowledge (later proven to be conflicting), the initial hypothesis was a simple signal inversion issue.
* **Troubleshooting Path:**
    * Software Inversion: Attempts to use `SoftwareSerial` with an inversion flag failed, producing "all zeros."
    * Hardware Inversion: A transistor-based inverter circuit was built and tested. This also failed, producing "all zeros," which correctly proved the problem was not a simple inversion, though this was not understood at the time.
    * Component Swapping: Multiple transistors and a brand-new FS-R7P receiver were swapped in, all with the same "all zeros" result, correctly ruling out individual component failure.
    * Sanity Check: Reverted to the initial v1.2 sketch and direct connection, successfully reproducing the original "garbled data" result. This proved the receiver's i-BUS port was still electrically active.

**Status:** The initial diagnostic tests were inconclusive but successfully narrowed the problem down to a software or timing incompatibility. This proved that the standard libraries and methods were insufficient for this hardware combination and necessitated a deeper, more fundamental approach to the problem.

---
## October 11-12, 2025: Session 5 - In-Depth i-BUS Protocol Diagnostics

**Summary:** Performed an exhaustive, multi-day, hands-on diagnostic of the Flysky i-BUS protocol with the Arduino Nano Every. After numerous failed attempts using standard libraries and hardware configurations, it was determined that the available tools were insufficient and a different approach was needed.

**Log Details:**
* **Environment Setup:** Successfully configured a local, native Windows development environment using VS Code and PlatformIO, resolving all initial setup issues.
* **Extensive Testing:** A comprehensive series of tests were conducted using multiple i-BUS libraries (`IBusBM`, `FlySkyIBus`), hardware configurations (signal inverters, different pins), and software configurations (`SoftwareSerial`, manual register settings). All tests failed to produce a clean data stream, leading to an incorrect initial diagnosis of a toolchain incompatibility.
* **Hardware Verified:** All physical hardware (three receivers, Arduino, power sources, and wiring) was repeatedly tested and verified to be fully functional.
* **Decision:** Instead of abandoning the i-BUS protocol, the decision was made to step back and re-evaluate the problem from a first-principles, data-driven approach, analyzing the raw serial output directly.

**Status:** The diagnostic phase using standard libraries is complete. The project is paused pending a deeper, low-level analysis of the raw i-BUS data stream.

---
## October 12, 2025: Session 6 - Breakthrough: Custom i-BUS Parser Development

**Summary:** After stepping back to analyze the problem from the ground up, a successful, library-free solution for reading i-BUS data on the Arduino Nano Every was developed through a systematic, first-principles debugging process.

**Log Details:**
* **Root Cause Identified:** A deep dive into the raw hexadecimal data stream revealed that the initial "garbled" data was, in fact, valid i-BUS data being misinterpreted due to an incorrect serial port frame configuration. The issue was not signal inversion or a library bug, but a serial framing error.
* **Custom Parser Developed:** A new diagnostic sketch (`eureka_ibus.ino`) was created from scratch. This sketch implements a custom, lightweight state machine to read the i-BUS packet byte-by-byte.
* **The "Eureka" Fix:** The breakthrough was the manual configuration of the `Serial1` port to the correct **8-bit, Even Parity, 2-stop bit (8E2)** format using direct register manipulation (`UCSR1C = ...`). This, combined with the custom checksum validation, allowed for the first-ever successful decoding of all 14 i-BUS channels.
* **Data Translation:** It was confirmed that the raw channel values were "ticks," which were successfully converted to the standard `1000-2000` microsecond range using a simple mapping function.

**Status:** A robust, working solution for reading i-BUS data on the Nano Every has been achieved. The i-BUS diagnostic phase is officially complete and successful. The project can now proceed with integrating this solution into the main light controller firmware.