#include <Arduino.h>
#include "ColorBlink.h"
#include <Adafruit_NeoPixel.h>

#define RGBPIN 5
#define LEDNR 1

ColorBlink::ColorBlink(Adafruit_NeoPixel led){
  Adafruit_NeoPixel _led = led;
};

void ColorBlink::red(){
  _led.setPixelColor(0, _led.Color(0, 255, 0));
}

void ColorBlink::green(){
  _led.setPixelColor(0, _led.Color(255, 0, 0));
}

void ColorBlink::blue(){
  _led.setPixelColor(0, _led.Color(0, 0, 255));
}
