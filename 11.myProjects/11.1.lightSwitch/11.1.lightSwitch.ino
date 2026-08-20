/*
  Author:
  Learning Intention: Students will use a range of simple sensors to control an LED UI

  Student Notes:
  1. Make sure you include a copy of your schematic
  2. Students should use either the button or potentiometer in an unconventional way

  3. Suggested Grove ports: Button D4, Potentiometer A0, LED D6, Light sensor A3
*/
class Led {
  private:
    int pin;          // properties: data each Led remembers
    bool isOn;

  public:
    Led(int ledPin) {  // constructor: runs when an object is created
      pin = ledPin;
      isOn = false;
    }

    void begin() {
      pinMode(pin, OUTPUT);
      digitalWrite(pin, LOW);
    }

    void turnOn() {    // methods: things every Led can do
      digitalWrite(pin, HIGH);
      isOn = true;
    }

    void turnOff() {
      digitalWrite(pin, LOW);
      isOn = false;
    }

    void toggle() {
      if (isOn) {
        turnOff();
      } else {
        turnOn();
      }
    }
};

  // the LED soldered onto the Uno itself


class Button {
  private:
    int pin;

  public:
    Button(int buttonPin) {
      pin = buttonPin;
    }

    void begin() {
      pinMode(pin, INPUT);
    }

    bool isPressed() {
      return digitalRead(pin) == HIGH; // Grove button reads HIGH when pressed
    }
};

Led moduleLed(6);
Led builtinLed(13);
Button myButton(4); // Grove button on D4

void setup() {
  moduleLed.begin();
  builtinLed.begin();
  myButton.begin();
  builtinLed.turnOn();
}

void loop() {
  if (myButton.isPressed()) {
    moduleLed.toggle();
    builtinLed.toggle();
    delay(500);
  }
}
