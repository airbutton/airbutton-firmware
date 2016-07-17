#include "config.h"
#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include <ColorBlink.h>

Adafruit_NeoPixel led = Adafruit_NeoPixel(1, RGBPIN, NEO_GRB + NEO_KHZ800);
ColorBlink blinkLed = ColorBlink();

void setup() {
  Serial.begin(115200);
  Serial.println("Initial");
  led.setPixelColor(0, 0, 0, 0);
  led.show();
  Serial.println("Setup terminated");
}

// the loop function runs over and over again forever
void loop() {
  Serial.println("Initial Loop");
  blinkLed.red(&led, 1500, 2);
  //blinkLed.green(&led, 100, 10);
  //blinkLed.blue(&led, 50,50);
}
