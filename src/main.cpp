#include "Arduino.h"
#include <FastLED.h>

#define LED_PIN       19
#define POT_PIN       21
#define LEDS_PER_SEC  72
#define NUM_SECTIONS  10
#define NUM_LEDS      (LEDS_PER_SEC * NUM_SECTIONS)

CRGB leds[NUM_LEDS];

const CRGB COLOR_WARM = CRGB(255, 147, 41);
const CRGB COLOR_COOL = CRGB(200, 220, 255);

int snakeToLogical(int i) {
  int sec = i / LEDS_PER_SEC;
  int pos = i % LEDS_PER_SEC;
  if (sec % 2 == 1) pos = LEDS_PER_SEC - 1 - pos;
  return sec * LEDS_PER_SEC + pos;
}

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(8);
  pinMode(POT_PIN, INPUT);

  for (int i = 0; i < NUM_LEDS; i++) {
    int logical = snakeToLogical(i);
    uint8_t frac = (logical * 255UL) / (NUM_LEDS - 1);
    leds[i] = blend(COLOR_WARM, COLOR_COOL, frac);
  }

  FastLED.show();
}

void loop() {
  // Раскомментируйте, когда подключите потенциометр на пин 21:
  // int pot = analogRead(POT_PIN);
  // uint8_t br = map(pot, 0, 4095, 2, 255);
  // FastLED.setBrightness(br);
   FastLED.show();
   delay(50);
}