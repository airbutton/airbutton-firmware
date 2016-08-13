#ifndef CUSTOMURL_H
#define CUSTOMURL_H

#include <Arduino.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>
#include <ColorBlink.h>

extern Adafruit_NeoPixel led;
extern ColorBlink blinkLed;

String get_base_host();
String get_base_host();

boolean customurl();
void handleCustomURL();
void handleSetCustomURL();

#endif // CUSTOMURL_H
