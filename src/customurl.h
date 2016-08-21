#ifndef CUSTOMURL_H
#define CUSTOMURL_H

#include <Arduino.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>
#include <ColorBlink.h>
#include <EEPROMconfig.h>
#include "setupmode.h"

extern EEPROMconfig ABconfigs;
extern Adafruit_NeoPixel led;
extern ColorBlink blinkLed;

boolean customurl();

void handleCustomURL();

void handleSetCustomURL();

#endif // CUSTOMURL_H
