// Project: Ultrasonic Distance RGB Indicator
// Board: Arduino UNO R4 Minima
// Author: Aryan (ARYAN BUILDS)
// Description: Changes RGB LED color based on object distance (Green/Yellow/Red)

// ─── PIN DEFINITIONS ───────────────────────────────────────────────
#define TRIG_PIN   9    // HC-SR04 Trigger pin → sends the sound pulse
#define ECHO_PIN   10   // HC-SR04 Echo pin → receives the returning pulse

#define RED_PIN    3    // RGB LED Red channel (PWM pin ~3)
#define GREEN_PIN  5    // RGB LED Green channel (PWM pin ~5)
#define BLUE_PIN   6    // RGB LED Blue channel (PWM pin ~6)

// ─── DISTANCE THRESHOLDS (in centimeters) ──────────────────────────
#define CLOSE_DISTANCE  10   // Below this = RED (danger zone)
#define MID_DISTANCE    30   // Below this = YELLOW (caution zone)
                              // Above MID_DISTANCE = GREEN (safe zone)

// ─── SETUP ─────────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);  // Always 115200 for R4 Minima — check your Serial Monitor!

  // HC-SR04 pin modes
  pinMode(TRIG_PIN, OUTPUT);  // TRIG sends out the pulse — it's an output
  pinMode(ECHO_PIN, INPUT);   // ECHO receives the bounce — it's an input

  // RGB LED pin modes
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // Start with LED off (all HIGH because Common Anode logic is inverted)
  setColor(0, 0, 0);

  Serial.println("=== Ultrasonic RGB Distance Indicator ===");
  Serial.println("Ready! Bring your hand close to the sensor.");
}

// ─── MAIN LOOP ─────────────────────────────────────────────────────
void loop() {
  long distance = getDistance();  // Get distance in cm

  // Print to Serial Monitor so you can watch live values
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm  →  ");

  // Decide which color to show based on distance
  if (distance < CLOSE_DISTANCE) {
    // Object is CLOSE → RED
    setColor(255, 0, 0);
    Serial.println("🔴 RED - TOO CLOSE!");

  } else if (distance < MID_DISTANCE) {
    // Object is at MID range → YELLOW (Red + Green mixed = Yellow)
    setColor(255, 255, 0);
    Serial.println("🟡 YELLOW - Getting closer...");

  } else {
    // Object is FAR → GREEN
    setColor(0, 255, 0);
    Serial.println("🟢 GREEN - All clear!");
  }

  delay(100);  // Small pause to avoid flooding the Serial Monitor
}

// ─── FUNCTION: Get Distance from HC-SR04 ───────────────────────────
long getDistance() {
  // Step 1: Make sure TRIG is LOW first (clean state)
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);  // Wait 2 microseconds

  // Step 2: Send a 10-microsecond HIGH pulse on TRIG
  // This tells the sensor to fire a sound burst
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Step 3: Measure how long ECHO stays HIGH (in microseconds)
  // pulseIn() waits for the pin to go HIGH, then times how long it stays HIGH
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Step 4: Convert time to distance
  // Sound travels at ~343 m/s = 0.0343 cm/microsecond
  // The pulse travels TO the object and BACK, so divide by 2
  // distance = (duration × 0.0343) / 2  →  simplified: duration / 58
  long distance = duration / 58;

  return distance;
}

// ─── FUNCTION: Set RGB LED Color ───────────────────────────────────
// r, g, b values: 0 = OFF, 255 = FULL BRIGHTNESS
// BUT because your LED is Common Anode, we INVERT the values before writing
// 255 - 255 = 0  → analogWrite(pin, 0)   = full brightness (pin pulled LOW)
// 255 - 0   = 255 → analogWrite(pin, 255) = fully off     (pin pulled HIGH)
void setColor(int r, int g, int b) {
  analogWrite(RED_PIN,   255 - r);  // Invert because Common Anode
  analogWrite(GREEN_PIN, 255 - g);  // Invert because Common Anode
  analogWrite(BLUE_PIN,  255 - b);  // Invert because Common Anode
}
