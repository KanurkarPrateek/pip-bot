// Test 4: the speaker. Plays a happy "bee-doo!" chirp every 2 seconds.
// Needs ESP32 Arduino core 3.x (uses the built-in ESP_I2S library, nothing to install).
#include <ESP_I2S.h>
#include "pins.h"

I2SClass i2s;
const int RATE = 22050;

// a tone that slides from f0 to f1 Hz over ms milliseconds
void chirp(float f0, float f1, int ms, float vol = 0.25) {
  const int n = RATE * ms / 1000;
  static int16_t buf[256];
  float phase = 0;
  for (int i = 0; i < n; i += 256) {
    int len = min(256, n - i);
    for (int j = 0; j < len; j++) {
      float t = float(i + j) / n;
      float f = f0 + (f1 - f0) * t;
      phase += 2 * PI * f / RATE;
      float env = min(1.0f, min(t * 20, (1 - t) * 8));   // soft start/stop, no clicks
      buf[j] = int16_t(sinf(phase) * env * vol * 32767);
    }
    i2s.write((uint8_t *)buf, len * sizeof(int16_t));
  }
}

void setup() {
  Serial.begin(115200);
  i2s.setPins(AMP_BCLK, AMP_LRC, AMP_DIN);
  if (!i2s.begin(I2S_MODE_STD, RATE, I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_MONO))
    Serial.println("I2S did not start - check the amp wiring");
}

void loop() {
  chirp(900, 1500, 90);
  delay(40);
  chirp(1300, 2100, 140);
  delay(2000);
}
