#ifndef IFTT_H
#define IFTT_H

#include <Arduino.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>
#include <ColorBlink.h>
#include "setupmode.h"

extern Adafruit_NeoPixel led;
extern ColorBlink blinkLed;

String get_ifttt_key();
String get_ifttt_event();

boolean ifttt();
void handleIFTTT();
void handleSetIFTTT();

#endif // IFTT_H
