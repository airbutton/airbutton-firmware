#ifndef IFTT_H
#define IFTT_H

#include <Arduino.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>
#include <ColorBlink.h>

String get_ifttt_key();
String get_ifttt_event();
boolean ifttt(Adafruit_NeoPixel *led,ColorBlink *blinkLed);

#endif // IFTT_H
