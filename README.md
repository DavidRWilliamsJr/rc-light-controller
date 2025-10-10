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