#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <EEPROM.h>

#include "config.h"
#include "utils.h"
#include "setupmode.h"
#include "ifttt.h"
#include "customurl.h"

void setup(){
    //Wipe EEPROM for testing only!
    //wipeEEPROM();
    //Set WiFi to station mode
    WiFi.mode(WIFI_STA);
    //Set GPIO4 to HIGH for retain on APixel board useless on others boards
    pinMode(RETPIN, OUTPUT);
    digitalWrite(RETPIN, HIGH);
    //Init Serial port and EEPROM
    Serial.begin(115200);
    EEPROM.begin(512);
    //Init RGB LED
    led.begin();
    led.show();
    blinkLed.green(&led, 100, 2);

    //Try to load saved config
    if (!loadWiFiSavedConfig()) {
        Serial.println("WARNING: WiFi configuration not found");
        blinkLed.red(&led, 100, 2);
        setupMode();
        return;
    }

    //Check connection
    if (!checkWiFiConnection()) {
        Serial.println("ERROR: Connection lost");
        blinkLed.red(&led, 100, 2);
        setupMode();
        return;
    }
    //Button is connected! try to call to IFTTT

    for (int i = 0; i < 3; i++) {
        if (ifttt()) {
            Serial.println("Success ifttt!");
            blinkLed.green(&led, 100, 2);
            break;
        } else {
            Serial.println("WARNING: IFTTT failed! attempt nr " + i);
            blinkLed.red(&led, 100, 2);
        }
    }

    //Button is connected! try to call to IFTTT
    for (int i = 0; i < 3; i++) {
        if (customurl()) {
            Serial.println("Success custom url!");
            blinkLed.green(&led, 100, 2);
            break;
        } else {
            Serial.println("WARNING: Custom URL failed! attempt nr " + i);
            blinkLed.red(&led, 100, 2);
        }
    }

    if (APixelBoard) {
        //put retain pin to LOW for power off APixel board
        Serial.println("WARNING: APixel Board power off");
        APixelPowerOff(RETPIN);
    } else {
        Serial.println("WARNING: Deep Sleep Mode");
        powerOff();
    }
    //If chip is still on, button is pressed (Apixel board)
    Serial.println("WARNING: Button pressed ");
    setupMode();
}

void loop() {
    if (setupModeStatus) {
        WEB_SERVER.handleClient();
        blinkLed.violet(&led, 0,10);
        if ((millis()-startTime) > TIMEOUT){
            Serial.println("Set up mode timed out.");
            Serial.println("WARNING: APixel Board power off");
            delay(1000);
            APixelPowerOff(RETPIN);
        }
    } else {
        Serial.println("ERROR: Something wrong :-( ");
        blinkLed.red(&led, 200, 1);
        blinkLed.blue(&led, 200, 1);
        blinkLed.green(&led, 200, 1);
    }
}
