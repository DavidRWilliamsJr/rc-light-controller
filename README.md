# RC Crawler Light Controller

An Arduino-based, feature-rich light controller for a custom RC crawler, built on the PlatformIO IDE.

## Project Goal
To develop a custom, PCB-based light controller using an Arduino Nano Every. The system will manage standard and addressable LEDs based on RC inputs (via the Flysky i-BUS protocol) and sensor data, with a non-blocking, state-machine-based software architecture.

## Key Features
-   Brake, reverse, and "hold brake" lights based on RC throttle input.
-   Automatic headlights/tail lights via a photocell.
-   Automatic hazard lights linked to a 2-speed transmission servo channel.
-   Underbody "rock lights" that flash red under high motor current (ACS712).
-   Support for both gyro-enabled (FS-R7V) and standard (FS-R7P) receivers with automatic detection.

## Development Environment
This project is configured for the **PlatformIO IDE** within Visual Studio Code. All necessary libraries are "vendored" (included) in the `lib` folder for a self-contained, portable development environment.

-   **Board:** Arduino Nano Every
-   **Framework:** Arduino
-   **Core Libraries:**
    -   `FastLED` for addressable LED control.
    -   `IBusBM` for Flysky i-BUS communication.
    -   `VarSpeedServo` and `Streaming` for utility functions.

## Current Status
-   **Hardware:** Final design complete. All datasheets and a full Bill of Materials are located in the `/docs` folder. The project is physically on hold pending acquisition of a reliable 3S-rated 5V UBEC.
-   **Software:** The main software framework (`v0.5`) is feature-complete and compiles successfully. A separate `ibus_diagnostic.ino` sketch is also complete and compiled, ready for hardware testing.
-   **Next Step:** Perform initial hardware validation by running the diagnostic sketch with an FS-R7P receiver.
# RC Light Controller: Technical Contract (v3.0)

## 🎯 Current Project Goal
A simplified system using SparkFun COM-12986 (APA106) Addressable LEDs and an Arduino Nano Every.

## 📍 Hardware Source of Truth
* **MCU:** Arduino Nano Every (5V Logic)
* **Receiver:** FlySky FS-R7P (i-BUS)
* **LED Type:** SparkFun COM-12986 (APA106 Addressable RGB)
* **Library:** FastLED (configured for 'NEOPIXEL' or 'APA106')

## 📍 Pin Assignment Contract (v3.0 - Dual Chain)
| Function | Physical Pin | Pin (Logical) | Notes |
| :--- | :--- | :--- | :--- |
| **i-BUS RX** | RX0 | 0 | Hardware Serial1 |
| **Chassis LEDs** | D2 | 5 | Undercarriage Rock Lights |
| **Body LEDs** | D4 | 7 | Hazards/Brakes (Removable) |

## ⚠️ Physical Connection Map (COM-12986 Pinout)
*Holding LED with pins facing you, flat side on the right:*
1. **Data In (DI):** Connects to Arduino Pin D2.
2. **Power (VCC):** Connects to 5V Rail.
3. **Ground (GND):** Connects to GND.
4. **Data Out (DO):** Connects to Pin 1 of the NEXT LED in the chain.

## 📐 Logical Constraints
1. **Timing:** Use `FastLED.addLeds<APA106, 2, RGB>(leds, NUM_LEDS);`.
2. **Current:** Limit brightness to 50% in setup to protect the 600mA buck converter.
3. **Wiring:** All LEDs are wired in a "Daisy Chain" (DO to DI).

## 📐 Physical Wiring Strategy
1. **Chassis Chain:** Permanent wiring to rock light locations.
2. **Body Chain:** Connected via a removable 3-pin JST-style header to the main PCB.
3. **Power:** Both chains share a common 5V rail from the buck converter.

## 💻 FastLED Implementation Logic
- **Chassis:** `FastLED.addLeds<APA106, 2, RGB>(leds_chassis, NUM_CHASSIS);`
- **Body:** `FastLED.addLeds<APA106, 4, RGB>(leds_body, NUM_BODY);`
- **Safety:** Brightness globally limited to 128 (50%) to prevent overcurrent.