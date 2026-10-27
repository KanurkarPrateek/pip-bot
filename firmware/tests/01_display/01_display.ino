// Test 1: the screen. Shows two cyan eyes that blink.
// Library: "GFX Library for Arduino" (by moononournation) from the Library Manager.
#include <Arduino_GFX_Library.h>
#include "pins.h"

Arduino_DataBus *bus = new Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCK, TFT_MOSI, GFX_NOT_DEFINED);
// rotation 1 = landscape (280 wide x 240 tall). 'true' = IPS panel. The 1.69" panel has a 20 px offset.
Arduino_GFX *gfx = new Arduino_ST7789(bus, TFT_RST, 1, true, 240, 280, 0, 20, 0, 20);

const uint16_t BG = 0x0000, CYAN = 0x5F3F;

void eyes(int h) {
  gfx->fillRect(40, 30, 200, 180, BG);
  int y = 120 - h / 2;
  gfx->fillRoundRect(70, y, 56, h, min(16, h / 2), CYAN);
  gfx->fillRoundRect(154, y, 56, h, min(16, h / 2), CYAN);
}

void setup() {
  Serial.begin(115200);
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);           // backlight on
  if (!gfx->begin()) Serial.println("Display did not start - check wiring");
  gfx->fillScreen(BG);
  gfx->setTextColor(0xFFFF);
  gfx->setCursor(92, 218);
  gfx->print("hi, I'm Pip");
  eyes(80);
}

void loop() {
  delay(2500);
  for (int h : {50, 20, 6, 20, 50, 80}) { eyes(h); delay(25); }   // blink
}
