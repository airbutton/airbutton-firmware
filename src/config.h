#ifndef CONFIG_H
#define CONFIG_H

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Global config
#define RGBPIN 5
#define LEDNR 1
#define RETPIN 4
#define AP_SSID "gallAButton"
String DEVICE_TITLE="gallAButton";

// Global objects
Adafruit_NeoPixel led = Adafruit_NeoPixel(1, RGBPIN, NEO_GRB + NEO_KHZ800);
ColorBlink blinkLed = ColorBlink();

// Setup mode
boolean setupModeStatus = false;
const IPAddress AP_IP(192, 168, 5, 1);
String ssid = "";
String password = "";
String SSID_LIST = "";
ESP8266WebServer WEB_SERVER(80);

//TODO create a config page on web server
// IFTTT Definitions
const char* IFTTT_URL= "maker.ifttt.com";
String IFTTT_KEY= "caLX5eFSmUZaXFtXVyBAEB";
String IFTTT_EVENT = "button_pressed";
#endif
