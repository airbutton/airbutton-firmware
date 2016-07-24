#ifndef CONFIG_H
#define CONFIG_H

#include <ESP8266WebServer.h>

// Global config
#define RGBPIN 5
#define RETPIN 4
#define AP_SSID "gallAButton"
String DEVICE_TITLE="gallAButton";

// Global objects
Adafruit_NeoPixel led  = Adafruit_NeoPixel(1, RGBPIN, NEO_GRB + NEO_KHZ800);
ColorBlink blinkLed  = ColorBlink();
ESP8266WebServer  WEB_SERVER(80);

// Setup mode
boolean setupModeStatus = false;
const IPAddress AP_IP(192, 168, 5, 1);
String ssid = "";
String password = "";
String SSID_LIST = "";

//TODO create a config page on web server
// IFTTT Definitions
const char* IFTTT_URL= "maker.ifttt.com";
String IFTTT_KEY= "bh2t7puZws-85s9yA1d0kx";
String IFTTT_EVENT = "gallAButton";
#endif
