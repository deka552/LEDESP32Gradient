#include "Arduino.h"
#include <FastLED.h>

#define LED_PIN    19
#define NUM_LEDS   72   // 144/м × 0.5м
#define BRIGHTNESS 128
#define SPEED_MS   30

CRGB leds[NUM_LEDS];
uint8_t hue = 0;
int pos = 0;
bool forward = true;
unsigned long lastMove = 0;

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  unsigned long now = millis();
  if (now - lastMove < SPEED_MS) return;
  lastMove = now;

  fadeToBlackBy(leds, NUM_LEDS, 80);

  leds[pos] = CHSV(hue, 255, 255);
  hue++;

  pos += forward ? 1 : -1;
  if (pos >= NUM_LEDS) { pos = NUM_LEDS - 2; forward = false; }
  if (pos < 0)         { pos = 1;             forward = true;  }

  FastLED.show();
}