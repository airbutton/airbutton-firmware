#ifndef BLINK_H
#define BLINK_H

#include <Adafruit_NeoPixel.h>
#include "Arduino.h"

class Blink {
public:
  Blink();
  void red(Adafruit_NeoPixel);
private:
  Adafruit_NeoPixel a;
};

#endif
