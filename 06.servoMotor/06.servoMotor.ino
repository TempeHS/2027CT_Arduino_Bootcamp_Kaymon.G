/*
  Author:

  Learning Intention:
  The students will connect and control a positional servo motor with the Servo library.

  Success Criteria:
    1.  I understand how to connect the servo motor (Grove connector, signal on D3)
    2.  I can manually write different degrees of movement to the servo
    3.  I can map a potentiometer to a servo and control its movement
    4.  I understand the servo's angle is set by the width of each timed pulse
        sent from the microcontroller (the Servo library handles this)

  Hardware:
    Servo          -> Grove connector to D3 (yellow = signal)
    Potentiometer  -> A0
    Small servos can run from the shield's 5V. Larger servos need external power
    with a common ground (you will do this properly in 08.motorFundamentals).

  Optional breadboard reference:
    Bootcamp-servoMotor.png shows the same servo hand-wired without a Grove connector.

  Library setup (once):
    Open the bridge web interface, go to the Libraries tab, search for
    "Servo" (by Arduino) and install it. That provides the #include <Servo.h>
    used below.

  Documentation:
    https://www.sparkfun.com/servos
    https://github.com/arduino-libraries/Servo  <-- We are still using this library
*/

#include <Servo.h>

Servo myServo;

const int SERVO_PIN = A1;
const int POT_PIN = A0;

void setup() {
  pinMode(POT_PIN, INPUT);
  myServo.attach(SERVO_PIN);   // servo signal on D3
  myServo.write(90);           // move to the middle
}

void loop() {
  int value = analogRead(POT_PIN);
  int angle = map(value, 0, 1023, 0, 180);
  myServo.write(angle);

  }
      // move to the middle


