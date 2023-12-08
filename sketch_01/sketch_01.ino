#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned long startTime = 0;
unsigned long pauseTime = 0;
long elapsedTime = 0;
bool isRunning = false;
bool isButtonPressed = false;

const int startStopButtonPin = 4;
const int resetButtonPin = 2;

bool lastStartStopButtonState = false;
bool lastResetButtonState = false;
unsigned long debounceDelay = 50;

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();

  pinMode(startStopButtonPin, INPUT_PULLUP);
  pinMode(resetButtonPin, INPUT_PULLUP);
}

void loop() {
  if (isRunning) {
    elapsedTime = millis() - startTime;
  }

  displayElapsedTime();

  bool newStartStopButtonState = digitalRead(startStopButtonPin);
  bool newResetButtonState = digitalRead(resetButtonPin);

  if (newStartStopButtonState != lastStartStopButtonState) {
    if (newStartStopButtonState == HIGH) {
      if (!isRunning) {
        startStopwatch();
      } else if (!isButtonPressed) {
        stopStopwatch();
      }
      isButtonPressed = true;
    } else {
      isButtonPressed = false;
    }
  }

  if (newResetButtonState != lastResetButtonState) {
    if (newResetButtonState == HIGH) {
      resetStopwatch();
    }
  }

  lastStartStopButtonState = newStartStopButtonState;
  lastResetButtonState = newResetButtonState;
}

void startStopwatch() {
  if (isRunning == false && pauseTime != 0) {
    startTime = millis() - pauseTime;
    pauseTime = 0;
  } else {
    startTime = millis();
  }
  isRunning = true;
}

void stopStopwatch() {
  pauseTime = elapsedTime;
  isRunning = false;
}

void resetStopwatch() {
  startTime = 0;
  pauseTime = 0;
  elapsedTime = 0;
  isRunning = false;
}


void displayElapsedTime() {
  lcd.setCursor(0, 0);  // 상단 줄로 커서 이동

  if (isRunning) {
    lcd.print("Running:       ");
  } else {
    lcd.print("Stopped:       ");
  }

  lcd.setCursor(0, 1);  // 하단 줄로 커서 이동

  long seconds = elapsedTime / 1000;
  long minutes = seconds / 60;
  long hours = minutes / 60;

  lcd.print(hours);
  lcd.print("h ");
  lcd.print(minutes % 60);
  lcd.print("m ");
  lcd.print(seconds % 60);
  lcd.print("s");
}
