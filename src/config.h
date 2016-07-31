#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <ESP8266WebServer.h>

// Global config
#define APixelBoard true
#define RGBPIN 5
#define RETPIN 4
#define AP_SSID "gallAButton"
String DEVICE_TITLE="gallAButton";

// Setup mode
unsigned long startTime;
#define TIMEOUT (120*1000)  //Setupmode timeout in milliseconds
boolean setupModeStatus = false;
const IPAddress AP_IP(192, 168, 5, 1);
String ssid = "";
String password = "";
String SSID_LIST = "";

#endif
