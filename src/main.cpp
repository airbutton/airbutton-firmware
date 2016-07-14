#include "config.h"
#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include "Blink.h"

Adafruit_NeoPixel led = Adafruit_NeoPixel(1, RGBPIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  led.begin();
}

// the loop function runs over and over again forever
void loop() {
  Blink rosso = Blink();
  rosso.red();
  //  led.setPixelColor(0, led.Color(0, 0, 255));
  //  led.show();
  //  delay(500);
}
