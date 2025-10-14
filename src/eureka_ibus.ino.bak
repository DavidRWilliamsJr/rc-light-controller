// Final, Fully Calibrated i-Bus Parser
const int IBUS_MAX_CHANNELS = 14;
const int IBUS_BUFFER_SIZE = 40;
const unsigned long PRINT_INTERVAL = 100;
unsigned long last_print_time = 0;

// CALIBRATION VALUES
const int CH1_MIN_RAW = 50197;
const int CH1_MAX_RAW = 56556;
const int CH2_MIN_RAW = 8199;
const int CH2_MAX_RAW = 65031;
const int CH3_POS_LOW = 22480;
const int CH3_POS_HIGH = 56540;

byte ibus_buffer[IBUS_BUFFER_SIZE];
uint16_t ibus_raw_channels[IBUS_MAX_CHANNELS];
uint16_t ibus_mapped_channels[IBUS_MAX_CHANNELS];

byte packet_length = 0;
byte buffer_position = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("--- Final Calibrated i-Bus Parser ---");
  Serial1.begin(115200, SERIAL_8E2);
}

void loop() {
  while (Serial1.available() > 0) {
    byte input_byte = Serial1.read();
    if (buffer_position == 0 && input_byte == 0x20) {
      packet_length = input_byte;
      ibus_buffer[buffer_position++] = input_byte;
    } else if (buffer_position > 0) {
      if (buffer_position < IBUS_BUFFER_SIZE) {
        ibus_buffer[buffer_position++] = input_byte;
      } else {
        buffer_position = 0;
      }
      if (buffer_position >= packet_length) {
        int num_channels = (packet_length - 4) / 2;
        if (num_channels > IBUS_MAX_CHANNELS) num_channels = IBUS_MAX_CHANNELS;
        for (int i = 0; i < num_channels; i++) {
          int lsb_index = 2 + (i * 2);
          if ((lsb_index + 1) < packet_length) {
            ibus_raw_channels[i] = (uint16_t)(ibus_buffer[lsb_index + 1] << 8) | ibus_buffer[lsb_index];
          }
        }
        buffer_position = 0;
      }
    }
  }

  if (millis() - last_print_time >= PRINT_INTERVAL) {
    last_print_time = millis();
    ibus_mapped_channels[0] = map(ibus_raw_channels[0], CH1_MIN_RAW, CH1_MAX_RAW, 1000, 2000);
    ibus_mapped_channels[1] = map(ibus_raw_channels[1], CH2_MIN_RAW, CH2_MAX_RAW, 1000, 2000);
    if (ibus_raw_channels[2] < (CH3_POS_LOW + 1000)) {
      ibus_mapped_channels[2] = 1;
    } else if (ibus_raw_channels[2] > (CH3_POS_HIGH - 1000)) {
      ibus_mapped_channels[2] = 3;
    } else {
      ibus_mapped_channels[2] = 2;
    }
    for (int i = 3; i < IBUS_MAX_CHANNELS; i++) {
      ibus_mapped_channels[i] = ibus_raw_channels[i];
    }
    for (int i = 0; i < IBUS_MAX_CHANNELS; i++) {
      Serial.print("CH");
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(ibus_mapped_channels[i]);
      Serial.print("\t");
    }
    Serial.print("                                \r");
  }
}