// =================================================================
// Project:   i-BUS Receiver Diagnostic Tool
// Version:   11.0 (The Complete Fix - All Required Components)
// Date:      October 12, 2025
// Purpose:   To correctly read i-BUS data on a Nano Every by
//            implementing the full solution discovered in the
//            IBusBM GitHub issue tracker.
// =================================================================

// -- LIBRARIES --
// 1. This #define MUST come BEFORE the library is included to
//    configure the library during compilation.
#define IBUSBM_NOTIMER
#include <IBusBM.h>

// -- OBJECTS --
IBusBM ibus;

// -- TIMING VARIABLES for non-blocking delay --
unsigned long previousMillis = 0;
const long interval = 250; // How often to print (milliseconds)

// =================================================================
//   SETUP: Runs once at power-on
// =================================================================

// From example code used in troubleshoting by Bart
IBusBM IBusServo;
IBusBM IBusSensor;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("--- i-BUS Diagnostic Tool v11.0 (The Complete Fix) ---");

  // 2. Start the i-BUS listener on the hardware serial port and
  //    explicitly pass IBUSBM_NOTIMER as the second argument to
  //    disable the incompatible hardware timer at runtime.
  ibus.begin(Serial1, IBUSBM_NOTIMER);

  Serial.println("IBus.begin() with IBUSBM_NOTIMER flag is complete.");
}

// =================================================================
//   LOOP: Runs continuously
// =================================================================
void loop() {
  // 3. Call ibus.loop() on EVERY iteration of the main loop to
  //    ensure we never miss an incoming data packet.
  ibus.loop();

  // --- Non-Blocking Printing ---
  // Only print the channel data every 250ms to keep it readable.
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Print each channel's value.
    for (int i = 0; i < 14; i++) {
      Serial.print("CH");
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(ibus.readChannel(i));
      Serial.print("\t");
    }
    Serial.println();
  }
}