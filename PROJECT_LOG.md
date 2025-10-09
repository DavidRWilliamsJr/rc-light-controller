# Project Log: RC Light Controller

This document serves as the official engineering log, tracking all decisions, changes, and milestones for the project.

---
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
                