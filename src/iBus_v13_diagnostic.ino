// =================================================================
// Project:   i-BUS Receiver Diagnostic Tool
// Version:   13.0 (The "Eureka" Fix - User-Developed Custom Parser)
// Date:      October 12, 2025
// Purpose:   To correctly read i-BUS data on a Nano Every by
//            implementing the user-developed custom parser and
//            correct serial port configuration.
// Credit:    Solution developed by David Williams Jr.
// =================================================================

// -- GLOBAL VARIABLES --
byte ibusPacket[32];
int ibusChannels[14];

// -- TIMING VARIABLES for non-blocking delay --
unsigned long previousMillis = 0;
const long interval = 250; // How often to print (milliseconds)

// =================================================================
//   SETUP: Runs once at power-on
// =================================================================
void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("--- i-BUS Diagnostic Tool v13.0 (The Eureka Fix) ---");

  // --- THE EUREKA FIX ---
  // Initialize Serial1 and manually force the correct 8E1 configuration.
  Serial1.begin(115200);
  UCSR1C = (1 << UPM11) | (1 << UCSZ10) | (1 << UCSZ11);
  
  Serial.println("Serial1 started with correct 8E1 configuration.");
}

// =================================================================
//   LOOP: Runs continuously
// =================================================================
void loop() {
  if (readIbus()) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;

      for (int i = 0; i < 14; i++) {
        Serial.print("CH");
        Serial.print(i + 1);
        Serial.print(": ");
        // Convert the raw value to the standard 1000-2000 range
        Serial.print(map(ibusChannels[i], 21480, 54748, 1000, 2000));
        Serial.print("\t");
      }
      Serial.println();
    }
  }
}

// =================================================================
//   CUSTOM i-BUS PARSER (Developed by David Williams Jr.)
// =================================================================
bool readIbus() {
  static byte state = 0;
  static byte len = 0;
  static uint16_t checksum = 0;

  while (Serial1.available()) {
    byte b = Serial1.read();

    switch (state) {
      case 0: // Waiting for start bytes
        if (b == 0x20) {
          ibusPacket[0] = b;
          len = 1;
          state = 1;
        }
        break;

      case 1: // Reading the rest of the packet
        ibusPacket[len++] = b;
        if (len == 32) {
          state = 0; // Reset for the next packet

          if (ibusPacket[1] != 0x40) {
            return false;
          }

          checksum = 0xFFFF;
          for (int i = 0; i < 30; i++) {
            checksum -= ibusPacket[i];
          }

          uint16_t receivedChecksum = (ibusPacket[31] << 8) | ibusPacket[30];

          if (checksum == receivedChecksum) {
            for (int i = 0; i < 14; i++) {
              ibusChannels[i] = (ibusPacket[i * 2 + 3] << 8) | ibusPacket[i * 2 + 2];
            }
            return true; // Success!
          }
        }
        break;
    }
  }
  return false;
}