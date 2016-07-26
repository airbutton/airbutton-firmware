#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Adafruit_NeoPixel.h>
#include <ColorBlink.h>

// Load WiFi configuration from EEPROM
boolean loadWiFiSavedConfig();

// Wi-Fi check connection
boolean checkWiFiConnection(Adafruit_NeoPixel *led,ColorBlink *blinkLed);

// Wi-Fi access point list
String ssidList();

// HTML Page maker
String makePage(String DEVICE_TITLE, String title, String contents);

// Decode URL
String urlDecode(String input);

//Put the board in deepsleep mode
void powerOff();

// Wipe EEPROM
void wipeEEPROM();

#endif
