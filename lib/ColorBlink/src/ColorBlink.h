#ifndef COLORBLINK_H
#define COLORBLINK_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class ColorBlink {
public:
    ColorBlink();

    void red(Adafruit_NeoPixel *led, int time, int count);

    void green(Adafruit_NeoPixel *led, int time, int count);

    void blue(Adafruit_NeoPixel *led, int time, int count);

    void violet(Adafruit_NeoPixel *led, int time, int count);

private:
};

#endif
