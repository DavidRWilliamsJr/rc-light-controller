# RC Light Controller: Technical Contract (Hard Reset Feb 2026)

## 🎯 Current Scope
A stable, two-chain lighting system for a 1/18 scale RC truck. This design uses a removable connector for the body shell to allow easy maintenance.

## 🛠 Hardware Stack
* **Controller:** Arduino Nano Every (ATmega4809)
* **Power:** Adafruit UBEC (Product ID 1385) - 5V @ 3A Continuous
* **Receiver:** FlySky FS-R7P (i-BUS)
* **LED Type:** PTH APA106 Addressable RGB (SparkFun COM-12986)

## 📍 Pin Assignment Contract (LOCKED)
| Function | Logical Pin | Physical Pin | Connection / Group |
| :--- | :--- | :--- | :--- |
| **i-BUS RX** | 0 | RX0 | From FlySky FS-R7P |
| **Chassis LEDs** | 2 | D2 | Permanent Undercarriage Lights |
| **Body LEDs** | 4 | D4 | Body Shell (via 3-Pin JST) |
| **Reserved** | 3 | D3 | Digital/Interrupt Input |

## 📐 Implementation Constraints
1.  **Power:** LEDs are powered directly from the 3A UBEC rail. No software brightness limit is required for safety, though 50-70% is recommended for visual comfort.
2.  **LED Library:** Strictly use `FastLED`.
3.  **Timing:** APA106 timing must be explicitly set to avoid flickering.
4.  **Hardware Serial:** Use `Serial1` for i-BUS. Never use `SoftwareSerial` on the Nano Every.

## 🛑 AI Rules
- State "I don't know" if a request requires parts not listed in the BOM.
- Wiring diagrams must show the UBEC powering both the Arduino (via 5V pin) and the LED chains.