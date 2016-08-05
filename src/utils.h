#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>
#include <ColorBlink.h>

extern Adafruit_NeoPixel led;
extern ColorBlink blinkLed;

// Load WiFi configuration from EEPROM
boolean loadWiFiSavedConfig();

// Wi-Fi check connection
boolean checkWiFiConnection();

// Wi-Fi access point list
String ssidList();

// HTML Page maker
String makePage(String device_title,String page_title, String contents);

// Wipe EEPROM
void wipeEEPROM();

// Decode URL
String urlDecode(String input);

//Put the board in deepsleep mode
void powerOff();

//Power off APixelBoard
void APixelPowerOff(uint8_t pin);

#endif // UTILS_H
