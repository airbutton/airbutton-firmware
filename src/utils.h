#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>
#include <ColorBlink.h>
#include <ArduinoJson.h>
#include <FS.h>

extern Adafruit_NeoPixel led;
extern ColorBlink blinkLed;
extern "C" {
#include "user_interface.h"
}

// Load WiFi configuration
boolean loadWiFiSavedConfig();

// Wi-Fi check connection
boolean checkWiFiConnection();

// Wi-Fi access point list
String ssidList();

// HTML Page maker
String makePage(String device_title, String page_title, String contents);

// Decode URL
String urlDecode(String input);

//Put the board in deepsleep mode
void powerOff();

//Power off APixelBoard
void APixelPowerOff(uint8_t pin);

//get vcc
float vcc();

//Load and save config file from SPIFF
boolean printConfig();

boolean loadJsonParam(const char *service);

const char *loadJsonParam(const char *service, const char *param);

boolean saveJsonConfig(const char *service, const char *param, const char *config);

boolean saveJsonConfig(const char *service, const char *param, boolean status);

void debugSPIFFS();

#endif // UTILS_H
