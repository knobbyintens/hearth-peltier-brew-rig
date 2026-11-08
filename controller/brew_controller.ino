// Hearth Peltier brew rig controller
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "pid.h"

const uint8_t kPwmPin = 9;
const uint8_t kProbePin = A0;
const float kMaxCurrent = 18.0f;

LiquidCrystal_I2C lcd(0x27, 16, 2);
PidController pid(2.4f, 0.12f, 0.05f);

float readProbe() {
  int raw = analogRead(kProbePin);
  return 0.31f * raw - 4.0f;
}

void applyOutput(float duty) {
  if (duty < 0.0f) duty = 0.0f;
  if (duty > 1.0f) duty = 1.0f;
  int pwm = (int)(duty * 255.0f);
  analogWrite(kPwmPin, pwm);
}

void showState(float temp, float duty) {
  lcd.setCursor(0, 0);
  lcd.print("T=");
  lcd.print(temp, 1);
  lcd.print("C ");
  lcd.print("D=");
  lcd.print(duty * 100.0f, 0);
  lcd.print("%");
}

void setup() {
  pinMode(kPwmPin, OUTPUT);
  lcd.init();
  lcd.backlight();
  pid.setLimits(0.0f, 1.0f);
  pid.setSetpoint(65.0f);
}

void loop() {
  float temp = readProbe();
  float duty = pid.update(pid.setpoint(), temp, 0.5f);
  applyOutput(duty);
  showState(temp, duty);
  delay(500);
}
