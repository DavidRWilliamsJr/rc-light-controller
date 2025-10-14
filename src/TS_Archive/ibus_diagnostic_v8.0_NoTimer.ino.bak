// =================================================================
// Project:   i-BUS Receiver Diagnostic Tool
// Version:   8.0 (The Real Fix - IBUSBM_NOTIMER Mode)
// Date:      October 12, 2025
// Purpose:   To correctly read i-BUS data on a Nano Every by
//            using the author-recommended manual loop method.
// =================================================================

// -- LIBRARIES --
// This #define MUST come BEFORE the library is included.
// It disables the library's internal timer, which is incompatible
// with the Arduino Nano Every.
#define IBUSBM_NOTIMER
#include <IBusBM.h>

// -- OBJECTS --
// Initialize i-BUS object to listen on the second hardware
// serial port (Serial1), which corresponds to Pin D0 (RX).
IBusBM ibus;

// =================================================================
//   SETUP: Runs once at power-on
// =================================================================
void setup() {
  // Start the main serial port for debugging
  Serial.begin(115200);
  delay(1000);

  Serial.println("--- i-BUS Diagnostic Tool v8.0 (The Real Fix) ---");

  // Start the i-BUS listener on the hardware serial port.
  // No manual register configuration is needed with this method.
  ibus.begin(Serial1);

  Serial.println("IBus.begin() on Serial1 is complete.");
}

// =================================================================
//   LOOP: Runs continuously
// =================================================================
void loop() {
  // Because we used IBUSBM_NOTIMER, we are now responsible for
  // calling the loop() function ourselves to check for new data.
  ibus.loop();

  // Print each channel's value. The R7V may have up to 14 channels.
  for (int i = 0; i < 14; i++) {
    Serial.print("CH");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(ibus.readChannel(i));
    Serial.print("\t");
  }
  Serial.println();

  delay(250); // Slow down the printing for readability
}