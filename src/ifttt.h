#ifndef IFTTT_H
#define IFTTT_H

#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include <Adafruit_NeoPixel.h>
#include <ColorBlink.h>

String get_ifttt_key();
String get_ifttt_event();
boolean ifttt(Adafruit_NeoPixel *led,ColorBlink *blinkLed);

#endif // IFTTT_H
