// =================================================================
// Project:   i-BUS Receiver Diagnostic Tool
// Version:   5.0 (Final - IBusBM with Hardware Inverter)
// Date:      October 11, 2025
// Purpose:   To be used with an external hardware signal inverter and
//            the IBusBM library on a hardware serial port.
// =================================================================

// -- LIBRARIES --
#include <IBusBM.h>

// -- OBJECTS --
// Initialize i-BUS object to listen on the second hardware
// serial port (Serial1), which corresponds to Pin D0 (RX).
IBusBM ibus;

// =================================================================
//   SETUP: Runs once at power-on
// =================================================================
void setup() {
  // Start the main serial port for debugging (to the computer)
  Serial.begin(115200);
  delay(1000);

  Serial.println("--- i-BUS Diagnostic Tool v5.0 ---");
  Serial.println("Using IBusBM library with hardware inverter on Pin RX (D0)");

  // Start the i-BUS listener on the reliable Hardware Serial port.
  ibus.begin(Serial1);

  Serial.println("IBus.begin() on Serial1 is complete.");
}

// =================================================================
//   LOOP: Runs continuously
// =================================================================
void loop() {
  // Call the library's loop() function to handle background data parsing.
  ibus.loop();

  // Print each channel's value using the correct readChannel() function.
  for (int i = 0; i < 10; i++) {
    Serial.print("CH");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(ibus.readChannel(i));
    Serial.print("\t");
  }
  Serial.println();

  delay(250); // Slow down the printing for readability
}