// Test 2: the servos.
// Step A (CENTER_ONLY = true): moves all 4 servos to 90 deg and holds them.
//   Do this BEFORE fitting the horns, arms and neck, then fit them pointing "straight / down".
// Step B (CENTER_ONLY = false): gently wiggles one servo at a time so you can check each one.
// Library: "ESP32Servo" (by Kevin Harrington) from the Library Manager.
// Power: servos need the robot's 5 V (switch ON). USB from the computer alone is not enough.
#include <ESP32Servo.h>
#include "pins.h"

const bool CENTER_ONLY = true;
const int PINS[4] = {SERVO_PAN, SERVO_TILT, SERVO_ARM_L, SERVO_ARM_R};
const char *NAMES[4] = {"pan (head turn)", "tilt (head nod)", "left arm", "right arm"};
Servo servo[4];

void setup() {
  Serial.begin(115200);
  for (int t = 0; t < 4; t++) ESP32PWM::allocateTimer(t);
  for (int i = 0; i < 4; i++) {
    servo[i].setPeriodHertz(50);
    servo[i].attach(PINS[i], 500, 2400);
    servo[i].write(90);
    delay(300);                          // start them one by one so the power doesn't dip
  }
  Serial.println("All servos at 90 degrees");
}

void loop() {
  if (CENTER_ONLY) return;
  for (int i = 0; i < 4; i++) {
    Serial.printf("Moving %s\n", NAMES[i]);
    // small safe moves: the head only nods +-15 deg
    int span = (i == 1) ? 15 : 30;
    for (int a : {90 - span, 90 + span, 90}) { servo[i].write(a); delay(600); }
  }
  delay(1500);
}
