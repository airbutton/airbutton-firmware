#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include "utils.h"
#include "setupmode.h"


extern String DEVICE_TITLE;

void handleNotFound();

void handleSettings();

void handleSetap();

#endif // WEBSERVER_H
