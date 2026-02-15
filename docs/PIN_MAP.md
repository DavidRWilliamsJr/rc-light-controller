# RC Light Controller Pin Map (v1.1)

This file is the absolute source of truth for physical and logical connections.

## 🔌 Power & Grounding Strategy
- **Drive System:** 3S LiPo -> Furitek Python Pro ESC -> FS-R7P Receiver.
- **Lighting System:** Isolated 2S LiPo (Original TRX-4M or XT-30) -> Adafruit 1385 UBEC.
- **Supply Rail:** 5V @ 3A from UBEC Output.
- **⚡ AIR-GAP SAFETY:** The Drive and Lighting systems are isolated. 
- **⚡ GROUNDING:** A single common ground connection must be established between the FlySky Receiver GND pin and the Arduino GND to maintain i-BUS signal integrity.
- **⚡ POWER ISOLATION:** The red (VCC) wire from the Receiver to the Arduino must be **Disconnected (NC)** to prevent the Drive battery from back-feeding the Light controller.

## 📍 Arduino Nano Every Pin Assignments

| Function | Logical Pin | Physical Pin | Type | Wire Color | Notes |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **i-BUS RX** | 0 | Pin 1 (RX0) | Hardware UART | Yellow | From FlySky (via 3.3V/5V Shifter) |
| **Chassis Data**| 2 | Pin 5 | FastLED/PWM | Orange | Chain 1: Rock/Undercarriage Lights |
| **Body Data** | 4 | Pin 7 | FastLED/PWM | Orange | Chain 2: Body Shell (via JST-XH) |
| **Common Ground**| GND | Pin 4/17 | Ground | Black | Common to UBEC, Arduino, & Receiver |
| **VCC Supply** | 5V | Pin 18 | 5V Input | Red | From Adafruit UBEC Output |

## 🧩 Interconnect Summary
- **Main Chassis to Body:** 3-Pin JST-XH (5V, GND, Data Pin 4).
- **Receiver to Controller:** 2-wire connection (GND, Data Pin 0). **VCC MUST REMAIN UNCONNECTED.**