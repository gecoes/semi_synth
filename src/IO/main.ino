// Pins
const int PIN_EDIT_MODE = 13;
const int PIN_CHANNEL = 12;
const int PIN_SIGNAL = 11;
const int PIN_POT_BUTTON = 2;
const int PIN_LED = 10;
const int PIN_POT = A0;

// Estat intern
bool editMode = false;
bool lastEditMode = false;

int selectedChannel = 0;
int selectedSignal = 0;
int selectedParam = 0;
int lastChannel = -1;
int lastSignal = -1;
int lastParam = -1;
int lastPotValue = -1;

unsigned long lastDebounce = 0;
const unsigned long debounceDelay = 200;

void setup() {
  Serial.begin(9600);

  pinMode(PIN_EDIT_MODE, INPUT_PULLUP);
  pinMode(PIN_CHANNEL, INPUT_PULLUP);
  pinMode(PIN_SIGNAL, INPUT_PULLUP);
  pinMode(PIN_POT_BUTTON, INPUT_PULLUP);
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);
}

void loop() {
  if (millis() - lastDebounce > debounceDelay) {
    if (digitalRead(PIN_EDIT_MODE) == LOW) {
      editMode = !editMode;
      digitalWrite(PIN_LED, editMode ? HIGH : LOW);
      sendEditMode();
      lastDebounce = millis();
    }

    if (editMode) {
      if (digitalRead(PIN_CHANNEL) == LOW) {
        selectedChannel = (selectedChannel + 1) % 32;
        sendStatusIfChanged();
        lastDebounce = millis();
      }

      if (digitalRead(PIN_SIGNAL) == LOW) {
        selectedSignal = (selectedSignal + 1) % 4;
        sendStatusIfChanged();
        lastDebounce = millis();
      }

      if (digitalRead(PIN_POT_BUTTON) == LOW) {
        selectedParam = (selectedParam + 1) % 5;
        sendStatusIfChanged();
        lastDebounce = millis();
      }

      int potValue = analogRead(PIN_POT);
      if (abs(potValue - lastPotValue) > 10) {
        lastPotValue = potValue;
        sendFullStatus(potValue);
      }

      delay(150);
    }
  }
}

void sendEditMode() {
  Serial.print("{\"editMode\":");
  Serial.print(editMode ? "true" : "false");
  Serial.println("}");
  lastEditMode = editMode;
  int initialPotValue = analogRead(PIN_POT);
  sendFullStatus(initialPotValue);
}

void sendStatusIfChanged() {
  if (selectedChannel != lastChannel || selectedSignal != lastSignal ||
      selectedParam != lastParam) {
    sendFullStatus(lastPotValue);
  }
}

void sendFullStatus(int potValue) {
  float mappedValue;

  switch (selectedParam) {
  case 0:
    mappedValue = map(potValue, 0, 1023, 50, 2000);
    break;
  case 1:
    mappedValue = potValue / 1023.0;
    break;
  case 2:
  case 3:
    mappedValue = map(potValue, 0, 1023, 0, 100);
    break;
  case 4:
  default:
    mappedValue = 0.0;
  }

  Serial.print("{\"channel\":");
  Serial.print(selectedChannel);
  Serial.print(",\"signal\":");
  Serial.print(selectedSignal);
  Serial.print(",\"param\":");
  Serial.print(selectedParam);
  Serial.print(",\"value\":");
  if (selectedParam == 4) {
    String waveType;
    if (potValue < 341)
      waveType = "sin";
    else if (potValue < 683)
      waveType = "square";
    else
      waveType = "saw";
    Serial.print(waveType);
  }

  else {
    Serial.print(mappedValue, 3);
  }
  Serial.println("}");

  lastChannel = selectedChannel;
  lastSignal = selectedSignal;
  lastParam = selectedParam;
}
