// Test 3: the touch pad. Open Serial Monitor (115200) and touch the pad.
// Note: the TTP223 calibrates itself at power-on - don't touch it while switching on.
#include "pins.h"

void setup() {
  Serial.begin(115200);
  pinMode(TOUCH_PIN, INPUT);
}

void loop() {
  static bool last = false;
  bool now = digitalRead(TOUCH_PIN) == HIGH;
  if (now != last) Serial.println(now ? "touched!" : "released");
  last = now;
  delay(20);
}
