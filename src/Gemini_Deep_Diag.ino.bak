// Raw i-Bus Hexadecimal Data Logger for Arduino Nano Every
// Connect FS-R7V i-Bus signal to pin D2 (Serial1 RX)

void setup() {
  // Initialize USB serial for debugging output
  Serial.begin(115200);
  while (!Serial); // Wait for Serial Monitor to connect
  Serial.println("--- i-Bus Raw Data Logger ---");
  Serial.println("Displaying incoming bytes from Serial1 in HEX format.");

  // Initialize hardware serial for i-Bus input
  Serial1.begin(115200);
}

void loop() {
  // Check if there is data available from the i-Bus receiver
  if (Serial1.available() > 0) {
    // Read one byte from the receiver
    byte received_byte = Serial1.read();

    // Print the byte to the Serial Monitor in HEX format
    // Add a leading zero if the number is less than 0x10 for uniform formatting
    if (received_byte < 0x10) {
      Serial.print("0");
    }
    Serial.print(received_byte, HEX);
    Serial.print(" "); // Add a space between bytes for readability
  }
}