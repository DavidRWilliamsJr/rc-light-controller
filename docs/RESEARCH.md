# Project Research Log

This document contains a log of all external research, articles, and forum posts used to solve problems during the development of this project.

---
### **October 12, 2025: i-BUS Protocol Investigation**

**Topic:** Debugging i-BUS communication failure with the Arduino Nano Every.

* **Source 1:** [Arduino Forum - Problem using IBusBM with Nano Every](https://forum.arduino.cc/t/problem-using-ibusbm-with-nano-every/1061552/16)
    * **Key Finding:** This was the breakthrough. A user with the exact same hardware (Nano Every) and library (`IBusBM`) discovered that the `Serial1` port does not default to the standard "8N1" configuration. The solution is a one-line code fix (`UCSR1C = 0;` or its modern equivalent) to manually force the serial port into the correct mode before initializing the library. This became the basis for our `v7.0` diagnostic sketch.

* **Source 2:** [GitHub - IBusBM Issue #16](https://github.com/bmellink/IBusBM/issues/16)
    * **Key Finding:** Confirms the issue from the Arduino Forum. Provides further evidence that the problem is a serial port configuration mismatch specific to the ATmega4809 chip and not a fault of the library or receiver.

* **Source 3:** [The Nerdy Engineer - iBus and Arduino](https://thenerdyengineer.com/ibus-and-arduino/)
    * **Key Finding (Contradictory):** This article explicitly stated that the i-BUS signal was **non-inverted**, which contradicted other sources. While it provided a good overview, this key piece of information was incorrect for our hardware combination and led us down the wrong diagnostic path for a time. It serves as a good reminder to verify information from multiple sources.

* **Source 4:** [Official Arduino Library Documentation - IBusBM](https://docs.arduino.cc/libraries/ibusbm/)
    * **Key Finding:** Verified that `IBusBM` is the correct library and confirmed the proper function names (`begin`, `loop`, `readChannel`), which was useful during our initial debugging.