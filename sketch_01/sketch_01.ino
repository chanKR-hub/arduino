#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned long startTime = 0;
long elapsedTime = 0;  // elapsedTime 변수를 long 자료형으로 변경
bool isRunning = false;

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
}

void loop() {
  if (isRunning) {
    elapsedTime = millis() - startTime;
  }

  displayElapsedTime();

  if (Serial.available() > 0) {
    char button = Serial.read();
    if (button == 's') {
      if (!isRunning) {
        startStopwatch();
      } else {
        stopStopwatch();
      }
    } else if (button == 'r') {
      resetStopwatch();
    }
  }
}

void startStopwatch() {
  startTime = millis();
  isRunning = true;
}

void stopStopwatch() {
  isRunning = false;
}

void resetStopwatch() {
  startTime = 0;
  elapsedTime = 0;
  isRunning = false;
}

void displayElapsedTime() {
  lcd.setCursor(0, 1);
  if (isRunning) {
    lcd.print("Running:");
  } else {
    lcd.print("Stopped:");
  }

  long seconds = elapsedTime / 1000;  // seconds 변수도 long 자료형으로 변경
  long minutes = seconds / 60;
  long hours = minutes / 60;

  lcd.print(hours);
  lcd.print("h ");
  lcd.print(minutes % 60);
  lcd.print("m ");
  lcd.print(seconds % 60);
  lcd.print("s");
}
