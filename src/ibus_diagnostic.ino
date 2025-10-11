// =================================================================
// Project:   i-BUS Receiver Diagnostic Tool
// Version:   3.0 (SoftwareSerial Inverted Signal Solution)
// Date:      October 11, 2025
// =================================================================

// -- LIBRARIES --
#include <Arduino.h>
#include <SoftwareSerial.h> // <-- Use the standard SoftwareSerial library
#include <FlySkyIBus.h>

// -- PIN DEFINITIONS --
#define IBUS_RX_PIN 8 // Use Pin 8 as our new, virtual RX pin

// -- OBJECTS --
// Create a new SoftwareSerial port. The "true" at the end enables
// the built-in signal inversion.
SoftwareSerial ibusSerial(IBUS_RX_PIN, IBUS_RX_PIN + 1, true);

// =================================================================
//   SETUP: Runs once at power-on
// =================================================================
void setup() {
  // Start the main serial port for debugging (to the computer)
  Serial.begin(115200);
  delay(1000); 
  
  Serial.println("--- i-BUS Diagnostic Tool v3.0 ---");
  Serial.println("Using SoftwareSerial with inversion on Pin 8.");

  // Start the i-BUS listener, but tell it to use our new
  // virtual (software) serial port instead of a hardware one.
  IBus.begin(ibusSerial); 

  Serial.println("IBus.begin() with SoftwareSerial is complete.");
}

// =================================================================
//   LOOP: Runs continuously
// =================================================================
void loop() {
  // Print each channel's value.
  for (int i = 0; i < 10; i++) {
    Serial.print("CH");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(IBus.readChannel(i));
    Serial.print("\t");
  }
  Serial.println();
  
  delay(250); // Slow down the printing to be human-readable
}