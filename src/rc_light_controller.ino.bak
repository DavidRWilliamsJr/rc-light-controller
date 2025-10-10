// =================================================================
// Project:   RC Light Controller
// Version:   0.5 (Feature-Complete Framework)
// Date:      October 9, 2025
// =================================================================

// -- LIBRARIES --
#include <IBusBM.h>
#include <FastLED.h>

// -- SETTINGS & MODE FLAGS --
#define SIMULATION_MODE 1 // Set to 1 for placeholder data, 0 for live RC data

// -- STATE DEFINITIONS --
#define STATE_STARTUP 0
#define STATE_GYRO_ACTIVE 1
#define STATE_NO_GYRO_FALLBACK 2

// -- PIN DEFINITIONS --
#define PIN_MODE_SWITCH 2
#define PIN_ACS712_IN A0
#define PIN_PHOTOCELL_IN A1

#define PIN_SERVO_OUT 13
#define PIN_LIGHT_BAR 5
#define PIN_HEADLIGHTS 9

#define PIN_CHASSIS_LED_DATA 7
#define PIN_BODY_LED_DATA 10

// -- FASTLED DEFINITIONS --
#define NUM_LEDS_CHASSIS 8 // Example: 8 rock lights
#define NUM_LEDS_BODY 16   // Example: 8 LEDs per side for tail lights

// -- RC CHANNEL DEFINITIONS --
#define THROTTLE_CENTER 1500
#define THROTTLE_DEADBAND 20

// -- SENSOR THRESHOLDS --
#define LIGHT_SENSOR_THRESHOLD 400   // For photocell (0-1023)
#define CURRENT_SENSOR_ZERO 512      // For ACS712 (0-1023)
#define CURRENT_SENSOR_THRESHOLD 50  // For rock light activation

// -- SMOOTHING DEFINITIONS --
#define NUM_SAMPLES 5 // Number of samples to average

// -- GLOBAL VARIABLES --
// System State
int g_state = STATE_STARTUP;
unsigned long g_startupTimer;

// Raw RC Data
int g_rcChannels[10];

// Smoothed RC Data
int g_steeringReadings[NUM_SAMPLES];
int g_throttleReadings[NUM_SAMPLES];
int g_readingIndex = 0;
int g_smoothedSteering;
int g_smoothedThrottle;

// FastLED arrays
CRGB g_chassisLeds[NUM_LEDS_CHASSIS];
CRGB g_bodyLeds[NUM_LEDS_BODY];

// -- OBJECTS --
IBusBM ibus;

// =================================================================
//   SETUP: Runs once at power-on
// =================================================================
void setup() {
  Serial.begin(115200);
  Serial.println("RC Light Controller v0.5 Booting...");

  ibus.begin(Serial1);

  // Initialize FastLED
  FastLED.addLeds<WS2812B, PIN_CHASSIS_LED_DATA, GRB>(g_chassisLeds, NUM_LEDS_CHASSIS);
  FastLED.addLeds<WS2812B, PIN_BODY_LED_DATA, GRB>(g_bodyLeds, NUM_LEDS_BODY);

  // Pin Modes
  pinMode(PIN_HEADLIGHTS, OUTPUT);

  // Initialize smoothing arrays
  for (int i = 0; i < NUM_SAMPLES; i++) {
    g_steeringReadings[i] = 1500;
    g_throttleReadings[i] = THROTTLE_CENTER;
  }
  
  Serial.println("Setup Complete.");
}

// =================================================================
//   LOOP: Runs continuously
// =================================================================
void loop() {
  readReceiverInputs();
  smoothInputs();
  manageSystemState();
  updateAllLights();
}

// =================================================================
//   CUSTOM FUNCTIONS
// =================================================================

void readReceiverInputs() {
#if SIMULATION_MODE == 1
  g_rcChannels[0] = 1500; // CH1: Steering
  g_rcChannels[1] = 1500; // CH2: Throttle
  g_rcChannels[2] = 1000; // CH3: 2-Speed Trans Servo
  g_rcChannels[7] = 1500; // CH8: Gyro data placeholder
#else
  if (ibus.read()) {
    for (int i = 0; i < 10; i++) {
      g_rcChannels[i] = ibus.getChannel(i);
    }
  }
#endif
}

void smoothInputs() {
  g_steeringReadings[g_readingIndex] = g_rcChannels[0];
  g_throttleReadings[g_readingIndex] = g_rcChannels[1];
  g_readingIndex = (g_readingIndex + 1) % NUM_SAMPLES;

  long steeringTotal = 0;
  long throttleTotal = 0;
  for (int i = 0; i < NUM_SAMPLES; i++) {
    steeringTotal += g_steeringReadings[i];
    throttleTotal += g_throttleReadings[i];
  }

  g_smoothedSteering = steeringTotal / NUM_SAMPLES;
  g_smoothedThrottle = throttleTotal / NUM_SAMPLES;
}

void manageSystemState() {
  if (g_state == STATE_STARTUP) {
    if (g_startupTimer == 0) {
      g_startupTimer = millis();
    }
    if (g_rcChannels[7] != 1500) {
      g_state = STATE_GYRO_ACTIVE;
    }
    if (millis() - g_startupTimer > 2000) {
      g_state = STATE_NO_GYRO_FALLBACK;
    }
  }
}

void updateAllLights() {
  // --- Brake and Reverse Logic ---
  if (g_smoothedThrottle < (THROTTLE_CENTER - THROTTLE_DEADBAND)) {
    // Reversing
    g_bodyLeds[0] = CRGB::Black; // Brake light OFF
    g_bodyLeds[1] = CRGB::Black; // Brake light OFF
    // (Code for reverse lights would go here)
  } else if (g_smoothedThrottle > (THROTTLE_CENTER + THROTTLE_DEADBAND)) {
    // Moving Forward
    g_bodyLeds[0] = CRGB::Black; // Brake light OFF
    g_bodyLeds[1] = CRGB::Black; // Brake light OFF
  } else {
    // Stopped (in deadband) -> BRAKE ON
    g_bodyLeds[0] = CRGB::Red; // Left brake light ON
    g_bodyLeds[1] = CRGB::Red; // Right brake light ON
  }
  
  // --- Automatic Headlight Logic ---
  int lightSensorValue = analogRead(PIN_PHOTOCELL_IN);
  if (lightSensorValue < LIGHT_SENSOR_THRESHOLD) {
    digitalWrite(PIN_HEADLIGHTS, HIGH);
  } else {
    digitalWrite(PIN_HEADLIGHTS, LOW);
  }
  
  // --- Hazard Light Logic ---
  if (g_rcChannels[2] < 1500) { // Assuming CH3, low gear
    // (Code for hazards ON)
  } else {
    // (Code for hazards OFF)
  }

  // --- High-Current Rock Light Logic ---
  int currentSensorValue = analogRead(PIN_ACS712_IN);
  if (abs(currentSensorValue - CURRENT_SENSOR_ZERO) > CURRENT_SENSOR_THRESHOLD) {
    // (Code for high-load rock lights)
  } else {
    // (Code for normal rock lights)
  }

  // --- Tell all LEDs to update! ---
  FastLED.show();
}
