#include<FastLED.h>

#define NUM_LEDS_PER_STRIP 10  // don't know how many leds per strip, probably more than 10...
CRGB leds[NUM_LEDS_PER_STRIP];

const int enA = 6; //enable pin for motor driver, must be PWM pim
const int forA = 7; //forward pin for motor driver
const int revA = 8; //reverse pin for motor driver, may not be needed...

const int redpin = 13;
const int greenpin = 12;
const int bluepin = 11;

// use addLeds once for each strip
void setup() {
  // tell FastLED that there is 10 leds on pin 3, must use PWM pin
  FastLED.addLeds<WS2811, 3>(leds, NUM_LEDS_PER_STRIP);

  // tell FastLED that there is 10 leds on pin 5, must use PWM pin
  FastLED.addLeds<WS2811, 5>(leds, NUM_LEDS_PER_STRIP);
  // repeat as needed if using more strips

  pinMode(redpin, INPUT);
  pinMode(greenpin, INPUT);
  pinMode(bluepin, INPUT);

  pinMode(enA, OUTPUT);
  pinMode(forA, OUTPUT);
  pinMode(revA, OUTPUT);

  analogWrite(enA, 0);
  digitalWrite(forA, LOW);
  digitalWrite(revA, LOW);
  
}

void loop() {

  // half brightness
  LEDS.setBrightness(128);
  // We only have two potentiometers on the BOM, one for motor driver and one for the lights
  // I think just using simple breadboard switches to control which color of light is showing would work pretty easily
  // I have like a bag of 50 and wont ever use more than like 5 so we can use those for the project
  if (digitalRead(redpin) == HIGH) {
    leds[NUM_LEDS_PER_STRIP] = CRGB::Red;
    FastLED.show();
  }
  else if (digitalRead(greenpin) == HIGH) {
    leds[NUM_LEDS_PER_STRIP] = CRGB::Green;
    FastLED.show();
  }
  else if (digitalRead(bluepin) == HIGH) {
    leds[NUM_LEDS_PER_STRIP] = CRGB::Blue;
    FastLED.show();
  }
  else {
    leds[NUM_LEDS_PER_STRIP] = CRGB::White;
    FastLED.show();
  }


  //measures the potentiometer that is connected to analog A0. Returns value 0-1023, 0 is 0 volts and 1023 is 5 volts
  volatile int x = analogRead(0);
  // change the 0-1023 value into a value from 0-255
  x = x / 4.0117;
  analogWrite(enA, x);
  // I think I saw somewhere that the pump we have carries a large amount of water when running at full speed so we will probably
  // only need values on the smaller end of 0-1023 so that means having the potentiometer at higher resistance
}
