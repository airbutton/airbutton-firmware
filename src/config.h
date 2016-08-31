#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <ColorBlink.h>

String Version = "v0.7.git";

//This for ESP.getVcc()
ADC_MODE(ADC_VCC)

//Board definition
boolean APixelBoard = true;

//PIN definitions
uint8_t RETPIN = 4;
uint8_t RGBPIN = 5;

//Global objects
Adafruit_NeoPixel led = Adafruit_NeoPixel(1, RGBPIN, NEO_GRB + NEO_KHZ800);
ColorBlink blinkLed = ColorBlink();
ESP8266WebServer WEB_SERVER(80);
DNSServer DNS_SERVER;

//Global vars
boolean setupModeStatus = false;

//Setup Mode Config
unsigned long startTime;
#define TIMEOUT (240*1000)  //Setupmode timeout in milliseconds
IPAddress AP_IP(192, 168, 5, 1);
String CHIP_ID = String(ESP.getChipId());
String DEVICE_TITLE = "AIRBUTTON";
String AP_SSID = "**" + DEVICE_TITLE + "-" + CHIP_ID + "**";
String SSID_LIST;

#endif // CONFIG_H
