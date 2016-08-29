#ifndef IFTTT_H
#define IFTTT_H

#include <Arduino.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>
#include <ColorBlink.h>
#include "setupmode.h"

extern Adafruit_NeoPixel led;
extern ColorBlink blinkLed;

boolean ifttt();

void handleIFTTT();

void handleSetIFTTT();

#endif // IFTTT_H
