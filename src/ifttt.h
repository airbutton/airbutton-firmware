#ifndef IFTT_H
#define IFTT_H

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

boolean ifttt();

void handleIFTTT();

void handleSetIFTTT();

#endif // IFTT_H
