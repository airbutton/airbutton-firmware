#include "config.h"
#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include "../lib/ColorBlink/src/ColorBlink.h"

Adafruit_NeoPixel led = Adafruit_NeoPixel(1, RGBPIN, NEO_GRB + NEO_KHZ800);
ColorBlink bl = ColorBlink(led);

void setup() {
  Serial.begin(115200);
  led.begin();
}

// the loop function runs over and over again forever
void loop() {
//  blink.red();
  //  led.setPixelColor(0, led.Color(0, 0, 255));
  //  led.show();
  //  delay(500);
}
