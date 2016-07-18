#include <Arduino.h>
#include "ColorBlink.h"
#include <Adafruit_NeoPixel.h>

ColorBlink::ColorBlink(){
};

void ColorBlink::red(Adafruit_NeoPixel *led, int time, int count){
  int i = 0;
  led->begin();
  while (count > i ){
    led->setPixelColor(0, led->Color(255, 0, 0, 0));
    led->show();
    delay(time);
    led->setPixelColor(0, led->Color(0, 0, 0, 0));
    led->show();
    delay(time);
    i++;
  };
};

void ColorBlink::green(Adafruit_NeoPixel *led, int time, int count){
  int i = 0;
  while (count > i ){
    led->setPixelColor(0, led->Color(0, 255, 0));
    led->show();
    delay(time);
    led->setPixelColor(0, led->Color(0, 0, 0));
    led->show();
    delay(time);
    i++;
  };
};

void ColorBlink::blue(Adafruit_NeoPixel *led, int time, int count){
  int i = 0;
  while (count > i ){
    led->setPixelColor(0, led->Color(0, 0, 255));
    led->show();
    delay(time);
    led->setPixelColor(0, led->Color(0, 0, 0));
    led->show();
    delay(time);
    i++;
  };
};
