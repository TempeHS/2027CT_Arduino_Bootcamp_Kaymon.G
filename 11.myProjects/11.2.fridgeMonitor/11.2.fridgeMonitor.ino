/*
  Author:
  Learning Intention: Students will build a monitoring system that watches
  conditions and raises alerts, like the guardian inside a smart fridge

  The build: FRIDGE MONITOR
  1. Calibrate the light sensor FIRST (see below), then set your threshold
  2. The light sensor detects the door opening (light floods into a dark fridge)
  3. If the door stays open longer than 10 seconds, sound the buzzer and flash
     the LED until the door closes
  4. Keep the loop non-blocking: use the millis() pattern for the alarm flash
     AND the Serial Plotter output (no delay() anywhere)
  5. Plot the light level and door state so you can watch your threshold work

  Calibration (why: every bench is different):
    Ambient light, sensor tolerance and how enclosed your "fridge" is all
    change the raw readings, so a threshold that works for one build fails on
    another. Upload a bare reader first:
        void setup() { Serial.begin(115200); }
        void loop()  { Serial.println(analogRead(A3)); delay(50); }
    Watch the Serial Plotter. Record the covered (door closed) and uncovered
    (door open) values, set your threshold roughly halfway between them, and
    keep both measurements as a comment: evidence the number is not a guess.

  Student Notes:
  1. Make sure you include a flowchart of your logic
  2. Stretch goal: add a second sensor (Temp & Humidity I2C) or an OLED dashboard

  Suggested Grove ports: Light A3, Buzzer D5, LED D6
*/
const int LIGHT_PIN = A3;
const int BUZZER_PIN = 5;
const int LED_PIN = 6;

// Calibration evidence:
// Covered / door closed: replace with your reading
// Uncovered / door open: replace with your reading
const int DOOR_OPEN_THRESHOLD = 500; // Set halfway between your two readings

const unsigned long ALARM_DELAY_MS = 10000;
const unsigned long FLASH_INTERVAL_MS = 250;
const unsigned long PLOT_INTERVAL_MS = 50;

unsigned long doorOpenedAt = 0;
unsigned long lastFlashAt = 0;
unsigned long lastPlotAt = 0;

bool doorWasOpen = false;
bool ledState = false;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(115200);
}

/*
Logic flowchart:
START
  |
Read light sensor
  |
Is light above threshold? -- no --> Reset timer and turn alarm off
  |
 yes
  |
Has door been open for 10 seconds? -- no --> Keep alarm off
  |
 yes
  |
Turn buzzer on and flash LED using millis()
  |
Print light level and door state for Serial Plotter
  |
REPEAT
*/
void loop() {
  unsigned long currentTime = millis();
  int lightLevel = analogRead(LIGHT_PIN);
  bool doorOpen = lightLevel > DOOR_OPEN_THRESHOLD;
  bool alarmActive = false;

  if (doorOpen) {
    if (!doorWasOpen) {
      doorOpenedAt = currentTime;
    }

    if (currentTime - doorOpenedAt >= ALARM_DELAY_MS) {
      alarmActive = true;
    }
  } else {
    doorOpenedAt = 0;
    ledState = false;
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
  }

  if (alarmActive) {
    digitalWrite(BUZZER_PIN, HIGH);

    if (currentTime - lastFlashAt >= FLASH_INTERVAL_MS) {
      lastFlashAt = currentTime;
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);
    }
  } else if (doorOpen) {
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
  }

  if (currentTime - lastPlotAt >= PLOT_INTERVAL_MS) {
    lastPlotAt = currentTime;
    Serial.print("Light:");
    Serial.print(lightLevel);
    Serial.print(" Door:");
    Serial.println(doorOpen ? 1 : 0);
  }

  doorWasOpen = doorOpen;
}
