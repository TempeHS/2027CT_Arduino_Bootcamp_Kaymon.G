/*
  Author:

  Learning Intention:
  The students will measure distance with the Grove 3-pin ultrasonic sensor using a
  library, and structure their code with functions (parameters, return values, tabs).

  Success Criteria:
    1.  I can connect the Grove 3-pin ultrasonic sensor (single signal pin)
    2.  I understand how the sensor times an echo to measure distance
    3.  I generally understand what a library is
    4.  I can get a distance from the ultrasonic sensor using the Ultrasonic library
    5.  I understand how a function is called
    6.  I can return values from a function and use the value in my code
    7.  I can pass values into my functions to make them more secure
    8.  I can separate my functions into a functions.ino tab to make my code manageable
    9.  I know the computation terms abstraction and encapsulation

  Hardware (Grove cable to the base shield):
    Ultrasonic sensor (3-pin) -> D2
    Buzzer module             -> D5  (proximity alarm task)
    LED module                -> D6  (proximity alarm task)

  Student Notes:
    The bundled Ultrasonic library (Ultrasonic.h / Ultrasonic.cpp in this folder,
    by Erick Simoes) supports the Grove 3-pin sensor with a single pin:
        Ultrasonic ultrasonic(2);   // Trig and Echo share D2
    Open Ultrasonic.cpp and find where the echo time is divided by 2!

  Optional breadboard reference:
    Bootcamp-ultrasonicSensor.png shows the 4-pin HC-SR04 version hand-wired.

  Documentation:
    https://github.com/ErickSimoes/Ultrasonic  <-- We are using this library
    https://www.tutorialspoint.com/arduino/arduino_ultrasonic_sensor.htm
*/

#include "Ultrasonic.h"

Ultrasonic ultrasonic(2);   // Grove 3-pin sensor: trigger and echo share D2



const int BUZZER_PIN = 5;
const int LED_PIN = 6;

void showAlert(int zone) {
  if (zone == 2) {                     // safe: silent, LED off
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
  } else if (zone == 1) {              // warning: LED on, slow beep
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000, 100);
    delay(500);
  } else {                             // danger (zone 0): LED on, fast beep
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 2000, 80);
    delay(120);
  }
}

void logStatus(int distance, int zone) {
  Serial.print("Distance:");
  Serial.print(distance);
  Serial.print(",Zone:");
  Serial.println(zone);
}


void setup() {
  Serial.begin(115200);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
}


int readDistance() {
  return ultrasonic.read();
}

int classifyZone(int distance, int nearLimit, int farLimit) {
  if (distance < nearLimit) {
    return 0;              // danger
  } else if (distance < farLimit) {
    return 1;              // warning
  }
  return 2;                // safe
}

void loop() {
  int distance = readDistance();
  int zone = classifyZone(distance, 10, 30);
  showAlert(zone);
  logStatus(distance, zone);
}
