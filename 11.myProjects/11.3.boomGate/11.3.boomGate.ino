/*
  Author:
  Learning Intention: Students will use an ultrasonic sensor to control a servo motor

  Student Notes:
  1. Make sure you include flow chart of your logic
  2. Students should aim to implement different logic approaches to the problem

  3. Suggested Grove ports: Ultrasonic D2 (single signal pin), Servo D3

  Logic flowchart:
  START
    |
  Measure distance
    |
  Is distance < threshold? -- no --> Gate closed / closing
    |
   yes
    |
  Gate open / opening
    |
  Hold open while car is present (state machine version)
    |
  After clear delay with no car, close gate
    |
  REPEAT

  Edge cases handled by the STATE MACHINE version (B):
  - Car stops under the gate: gate stays OPEN because distance stays below
    threshold (state remains HOLD_OPEN, never triggers CLOSING).
  - Second car arrives while closing: any close-range reading during CLOSING
    resets state back to OPENING instead of finishing the close.

  Version A (simple threshold) does NOT handle these edge cases well:
  it can start closing the instant distance clears, even briefly, causing
  a flickering gate if a car idles near the threshold.
*/

#include <Servo.h>

const int TRIG_PIN = 2;      // Single signal pin (trigger + echo)
const int SERVO_PIN = 3;
const int DISTANCE_THRESHOLD_CM = 20; // Calibrate for your setup

const int GATE_CLOSED_ANGLE = 0;
const int GATE_OPEN_ANGLE = 90;

Servo gateServo;

// ---- Choose ONE logic version by setting this flag ----
const bool USE_STATE_MACHINE = true; // true = Version B, false = Version A

// Version B state machine
enum GateState { CLOSED, OPENING, HOLD_OPEN, CLOSING };
GateState gateState = CLOSED;

const unsigned long CLEAR_DELAY_MS = 2000; // Wait before closing once clear
unsigned long lastCarSeenAt = 0;

long readDistanceCm() {
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  pinMode(TRIG_PIN, INPUT);
  long duration = pulseIn(TRIG_PIN, HIGH, 30000); // 30ms timeout
  if (duration == 0) {
    return 999; // No echo, treat as clear
  }
  return duration / 29 / 2; // Convert to cm
}

void setup() {
  gateServo.attach(SERVO_PIN);
  gateServo.write(GATE_CLOSED_ANGLE);
  Serial.begin(115200);
}

void loop() {
  long distance = readDistanceCm();
  bool carPresent = distance < DISTANCE_THRESHOLD_CM;

  Serial.print("Distance:");
  Serial.print(distance);
  Serial.print(" CarPresent:");
  Serial.println(carPresent ? 1 : 0);

  if (USE_STATE_MACHINE) {
    // ---- Version B: state machine ----
    switch (gateState) {
      case CLOSED:
        if (carPresent) {
          gateState = OPENING;
        }
        break;

      case OPENING:
        gateServo.write(GATE_OPEN_ANGLE);
        gateState = HOLD_OPEN;
        lastCarSeenAt = millis();
        break;

      case HOLD_OPEN:
        if (carPresent) {
          lastCarSeenAt = millis(); // Car still there, keep resetting timer
        } else if (millis() - lastCarSeenAt >= CLEAR_DELAY_MS) {
          gateState = CLOSING;
        }
        break;

      case CLOSING:
        if (carPresent) {
          // Second car arrived mid-close: reopen instead of finishing close
          gateState = OPENING;
        } else {
          gateServo.write(GATE_CLOSED_ANGLE);
          gateState = CLOSED;
        }
        break;
    }
  } else {
    // ---- Version A: simple threshold (no memory of state) ----
    if (carPresent) {
      gateServo.write(GATE_OPEN_ANGLE);
    } else {
      gateServo.write(GATE_CLOSED_ANGLE);
    }
  }

  delay(100); // Small pacing delay, not a blocking wait for logic
}
