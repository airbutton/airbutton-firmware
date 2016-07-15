#include "config.h"
#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include <ColorBlink.h>

Adafruit_NeoPixel led = Adafruit_NeoPixel(1, RGBPIN, NEO_GRB + NEO_KHZ800);
blinkLed = ColorBlink(led);

void setup() {
  Serial.begin(115200);
  Serial.println("Initial");
  led.begin();
  Serial.println("Setup terminated");
}

// the loop function runs over and over again forever
void loop() {
  Serial.println("Initial Loop");
   blinkLed.red();
    led.show();
    delay(1000);
    led.setPixelColor(0, led.Color(255, 0, 0));
    led.show();
    delay(1000);
}
