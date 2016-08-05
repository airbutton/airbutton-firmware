#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <ColorBlink.h>
#include <ESP8266WebServer.h>


//Board definition
boolean APixelBoard = true;

//PIN definitions
uint8_t RETPIN = 4;
uint8_t RGBPIN = 5;

//Global objects
Adafruit_NeoPixel led = Adafruit_NeoPixel(1, RGBPIN, NEO_GRB + NEO_KHZ800);
ColorBlink blinkLed = ColorBlink();
ESP8266WebServer WEB_SERVER(80);

//Global vars
boolean setupModeStatus = false;

//Setup Mode Config
unsigned long startTime;
#define TIMEOUT (120*1000)  //Setupmode timeout in milliseconds
IPAddress AP_IP(192, 168, 5, 1);
const char *AP_SSID = "gallAButton";
String DEVICE_TITLE = "gallAButton";
String SSID_LIST;

#endif // CONFIG_H
