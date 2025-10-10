// =================================================================
// Project:   i-BUS Receiver Diagnostic Tool
// Version:   1.2 (Correct Library Usage)
// Date:      October 10, 2025
// Purpose:   To read and display all channel data from a
//            Flysky i-BUS receiver for testing and calibration.
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

  // Give it a moment to initialize before we start printing.
  delay(1000);

  Serial.println("--- i-BUS Diagnostic Tool ---");
  Serial.println("Listening for receiver data...");

  // Start the second serial port to listen for the i-BUS receiver
  ibus.begin(Serial1);
}

// =================================================================
//   LOOP: Runs continuously
// =================================================================
void loop() {
  // CORRECTION: Call the library's loop() function. This function
  // handles all the background work of reading and parsing data.
  ibus.loop();

  // Now, we can simply read the channel data at any time. The values
  // will be automatically updated in the background by ibus.loop().
  for (int i = 0; i < 10; i++) {
    Serial.print("CH");
    Serial.print(i + 1); // Print channel 1-10 instead of 0-9
    Serial.print(": ");
    Serial.print(ibus.readChannel(i));
    Serial.print("\t"); // Use a tab for spacing
  }
  Serial.println(); // Move to the next line for the next packet

  // A small delay to keep the serial monitor from flooding
  // and becoming unreadable.
  delay(50);
}