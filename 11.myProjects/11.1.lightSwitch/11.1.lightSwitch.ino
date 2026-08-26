/*
  Author:
  Learning Intention: Students will use a range of simple sensors to control an LED UI

  Student Notes:
  1. Make sure you include a copy of your schematic
  2. Students should use either the button or potentiometer in an unconventional way

  3. Suggested Grove ports: Button D4, Potentiometer A0, LED D6, Light sensor A3
*/
const int LED_PIN = 6;
const int BUT_PIN = 4;

int mode = 0;
int lastButtonState = LOW;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUT_PIN, INPUT);
  Serial.begin(115200);
}

void loop() {
  int buttonState = digitalRead(BUT_PIN);

  // Change mode once when the button is pressed.
  if (buttonState == HIGH && lastButtonState == LOW) {
    mode++;
    if (mode > 2) {
      mode = 0;
    }

    Serial.print("LED mode: ");
    Serial.println(mode);
    delay(200); // Simple button debounce
  }

  lastButtonState = buttonState;

  if (mode == 0) {
    digitalWrite(LED_PIN, LOW);       // Off
  } else if (mode == 1) {
    digitalWrite(LED_PIN, HIGH);      // On
  } else {
    digitalWrite(LED_PIN, HIGH);      // Blink
    delay(300);
    digitalWrite(LED_PIN, LOW);
    delay(300);
  }
}
