#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include "utils.h"
#include "setupmode.h"


extern String DEVICE_TITLE;

//Web Server root
void handleNotFound();
void handleReboot();

//WiFi form and write down WiFi config
void handleWiFi();
void handleSetWiFi();

#endif // WEBSERVER_H
