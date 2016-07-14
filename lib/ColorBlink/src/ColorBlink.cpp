#include "Arduino.h"
#include "ColorBlink.h"
#include <Adafruit_NeoPixel.h>

#define RGBPIN 5
#define LEDNR 1

ColorBlink::ColorBlink(Adafruit_NeoPixel led){
  _led = led;
};

void ColorBlink::red(){
  _led.setPixelColor(0, _led.Color(0, 255, 0));
  _led.show();
  delay(500);
}
