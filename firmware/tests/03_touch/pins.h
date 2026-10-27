// Pip pin map — same as the electronics guide. Change here if you wire differently.
#pragma once
// Display (1.69" ST7789, 240x280, SPI)
#define TFT_SCK   12   // module pin "SCL"
#define TFT_MOSI  11   // module pin "SDA"
#define TFT_CS    10
#define TFT_DC     9
#define TFT_RST    8   // module pin "RES"
#define TFT_BL     7   // module pin "BLK" (backlight)
// Servos (SG90): orange wire = signal
#define SERVO_PAN    1
#define SERVO_TILT   2
#define SERVO_ARM_L  3
#define SERVO_ARM_R  4
// I2S amp (MAX98357A)
#define AMP_BCLK   5
#define AMP_LRC    6
#define AMP_DIN   13
// Touch (TTP223 "I/O" pin)
#define TOUCH_PIN 44
