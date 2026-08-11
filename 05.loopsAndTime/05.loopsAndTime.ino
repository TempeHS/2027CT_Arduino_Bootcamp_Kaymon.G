/*
  Author:

  Learning Intention:
  The students will apply loop logic (count, pre-test and post-test loops) and manage
  time responsively with millis() instead of blocking with delay().

  Success Criteria:
    1.  I understand loop logic is repeating (or not) based on a true or false answer
    2.  I can apply comparison operators in count (for) and pre-test (while) loops
    3.  I understand a post-test (do while) loop runs its body at least once
    4.  I can iterate over an array with a for-each loop
    5.  I can detect and fix an infinite loop
    6.  I understand why delay() is blocking and not preferred for time event management
    7.  I can use millis() and binary logic to trigger events by time
    8.  I can seed and generate a random number
    9.  I understand micros() exists for microsecond timing
    10. I can read a simple logic flowchart

  Hardware (Grove cables to the base shield):
    Button module  -> D4
    LED module     -> D6
    Buzzer module  -> D5

  Student Notes:
    See the four loop flowcharts in this folder's Readme.md.

  Optional breadboard reference:
    Bootcamp-workingWithTime.png in this folder.

  Documentation:
    https://www.arduino.cc/reference/en/#structure
    https://www.arduino.cc/reference/en/language/functions/time/millis/
    https://www.arduino.cc/reference/en/language/functions/random-numbers/random/
*/

const int BUTTON_PIN = 4;  // Grove Button on D4
const int BUZZER_PIN = 5;  // Grove Buzzer on D5
const int LED_PIN = 6;     // Grove LED on D6

void setup() {
  Serial.begin(115200);


  pinMode(BUTTON_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  randomSeed(analogRead(A0));  // simple seed source
  Serial.println("Reaction Timer Ready");

}

void loop() {
 // Make sure button is released before a new round
  while (digitalRead(BUTTON_PIN) == HIGH) {
    // wait
  }

  Serial.println("Get ready...");
  delay(random(2000, 5000));  // blocking is fine before timing starts

  digitalWrite(LED_PIN, HIGH);
  unsigned long startTime = millis();

  while (digitalRead(BUTTON_PIN) == LOW) {
    // wait for press (intentional empty loop)
  }

  unsigned long reactionMs = millis() - startTime;
  digitalWrite(LED_PIN, LOW);

  Serial.print("Reaction time: ");
  Serial.print(reactionMs);
  Serial.println(" ms");

  if (reactionMs < 250) {
    tone(BUZZER_PIN, 988, 100);
    delay(120);
    tone(BUZZER_PIN, 1319, 140);
  }

  delay(800);  // brief gap before next round
}
