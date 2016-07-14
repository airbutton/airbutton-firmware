#include "Arduino.h"
#include "Blink.h"
#include <Adafruit_NeoPixel.h>

#define RGBPIN 5
#define LEDNR 1

Blink::Blink(){
//  Adafruit_NeoPixel led = Adafruit_NeoPixel(LEDNR, RGBPIN, NEO_GRB + NEO_KHZ800);
};

void Blink::red(Adafruit_NeoPixel){
  a.setPixelColor(0, a.Color(0, 255, 0));
  a.show();
  delay(500);
}
