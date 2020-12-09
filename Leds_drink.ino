#include <FastLED.h>

#define NUM_LEDS        10
#define DATA_PIN         6
#define CORRECT_DOT      4
#define INITIAL_DELAY  250
#define DELAY_SHIFT     25

CRGB leds[NUM_LEDS];
volatile int8_t flag_int = 0;
volatile int8_t keeps_correct = 0;
int8_t dot;
int8_t correct_counter;


void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  pinMode(2, INPUT_PULLUP); // internal pull-up resistor
  attachInterrupt(digitalPinToInterrupt(2), button_press, FALLING);
  correct_counter = 0;

}

void loop() {

  for (dot = 0; dot < NUM_LEDS; dot++) {

    if (flag_int == 1) {
      if (keeps_correct == 1) {
        correct_lights();
        correct_counter++;
      } else {
        wrong_lights();
        correct_counter = 0;
      }
      flag_int = 0;
    }
    leds[dot] = CRGB::Blue;
    FastLED.show();
    // clear this led for the next time around the loop
    leds[dot] = CRGB::Black;
    delay(INITIAL_DELAY - correct_counter * DELAY_SHIFT);
  }
}

void button_press() {
  flag_int = 1;
  if ( dot == CORRECT_DOT) {
    keeps_correct = 1;
  } else {
    keeps_correct = 0;
  }
}

void correct_lights() {
  int8_t dot2;
  for (dot2 = 0; dot2 < NUM_LEDS; dot2++) {
    leds[dot2] = CRGB::Green;
    FastLED.show();
    leds[dot2] = CRGB::Green;
    delay(70);
  }
  for (dot2 = 0; dot2 < NUM_LEDS; dot2++) {
    leds[dot2] = CRGB::Black;
    FastLED.show();
  }
}
void wrong_lights() {
  int8_t dot2;
  for (dot2 = 0; dot2 < NUM_LEDS; dot2++) {
    leds[dot2] = CRGB::Red;
  }
  FastLED.show();
  delay(500);
  for (dot2 = 0; dot2 < NUM_LEDS; dot2++) {
    leds[dot2] = CRGB::Black;
  }
  FastLED.show();
  delay(500);
}
