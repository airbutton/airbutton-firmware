#ifndef COLORBLINK_H
#define COLORBLINK_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>


class ColorBlink {
public:
  ColorBlink(Adafruit_NeoPixel led);
  void red();
  void green();
  void blue();
private:
  Adafruit_NeoPixel _led;
};

#endif
