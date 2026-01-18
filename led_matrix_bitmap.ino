#include <SPI.h>

#include <Arduino.h>
#include <FastLED.h>
#include "bitmap.h"
#define NUM_LEDS 256
#define DATA_PIN 2
CRGB leds[NUM_LEDS];

#define bigyo dino


void drawBitmap(const long array[], int frame) {
  for (int col = 0; col < 32; col++) {
    for (int row = 0; row < 8; row++) {
      if (col % 2 == 0)
        leds[col * 8 + row] = pgm_read_dword(&(array[frame * 256 + col * 8 + row]));
      else
        leds[col * 8 + row] = pgm_read_dword(&(array[frame * 256 + col * 8 + 7 - row]));
    }
  }
  FastLED.show();
}


void drawBitmap2D(long *array[], int frame) {
  for (int col = 0; col < 32; col++) {
    for (int row = 0; row < 8; row++) {
      if (col % 2 == 0)
        leds[col * 8 + row] = pgm_read_dword(&(array[frame * 256][col * 8 + row]));
      else
        leds[col * 8 + row] = pgm_read_dword(&(array[frame * 256][col * 8 + 7 - row]));
    }
  }
  FastLED.show();
}

void setup() {
  FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(100);
}

void loop() {
  for (int i = 0; i < sizeof(bigyo)/NUM_LEDS/sizeof(long); i++) {
    drawBitmap(bigyo, i);
    delay(100);
  }
}
