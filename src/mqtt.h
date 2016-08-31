#ifndef MQTT_H
#define MQTT_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>
#include <ColorBlink.h>
#include <MQTTClient.h>
#include "setupmode.h"

extern Adafruit_NeoPixel led;
extern ColorBlink blinkLed;

boolean mqtt();

void handleMQTT();

void handleSetMQTT();

#endif // MQTT_H
