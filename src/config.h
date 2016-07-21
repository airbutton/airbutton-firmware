#ifndef CONFIG_H
#define CONFIG_H

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define RGBPIN 5
#define LEDNR 1
#define AP_SSID "gallAButton"
String DEVICE_TITLE="gallAButton";

Adafruit_NeoPixel led = Adafruit_NeoPixel(1, RGBPIN, NEO_GRB + NEO_KHZ800);
ColorBlink blinkLed = ColorBlink();

// Setup mode
boolean setupModeStatus = false;
//const char* AP_SSID = "gallAButton";
const IPAddress AP_IP(192, 168, 5, 1);
String ssid = "";
String password = "";
String SSID_LIST = "";
ESP8266WebServer WEB_SERVER(80);

#endif
