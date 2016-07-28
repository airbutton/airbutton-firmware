#include <Arduino.h>
#include <EEPROM.h>
#include <Adafruit_NeoPixel.h>
#include <ColorBlink.h>
#include <ESP8266WebServer.h>
#include "config.h"
#include "utils.h"

// Global objects
Adafruit_NeoPixel led  = Adafruit_NeoPixel(1, RGBPIN, NEO_GRB + NEO_KHZ800);
ColorBlink blinkLed  = ColorBlink();
ESP8266WebServer  WEB_SERVER(80);

#include "setup.h"
#include "ifttt.h"

void setup() {
    //Wipe EEPROM for testing only!
    //wipeEEPROM();
    WiFi.mode(WIFI_STA);
    //Set GPIO4 to HIGH for retain on APixel board useless on others boards
    pinMode(RETPIN, OUTPUT);
    digitalWrite(RETPIN, HIGH);
    // Init Serial port
    Serial.begin(115200);
    // Init EEPROM
    EEPROM.begin(512);
    // Init LED
    led.begin();
    led.show();
    blinkLed.green(&led, 50, 10);

    //Try to connect with saved config
    if (!loadWiFiSavedConfig()) {
        Serial.println("WARNING: WiFi configuration not found");
        blinkLed.red(&led, 50, 10);
        setupMode();
        return;
    }
    //Check connection
    if (!checkWiFiConnection(&led,&blinkLed)) {
        Serial.println("ERROR: Connection lost");
        blinkLed.red(&led, 50, 10);
        setupMode();
        return;
    }
    //Button is connected! try to call to IFTTT
    for (int i = 0; i < 3; i++) {
        if (ifttt()) {
            Serial.println("Success!");
            blinkLed.green(&led, 50, 10);
            break;
        } else {
            Serial.println("WARNING: IFTTT failed! attempt nr " + i);
            blinkLed.red(&led, 50, 10);
        }
    }

    if (APixelBoard) {
        //put retain pin to LOW for power off APixel board
        Serial.println("WARNING: APixel Board power off");
        digitalWrite(RETPIN, LOW);
    } else {
        Serial.println("WARNING: Deep Sleep Mode");
        powerOff();
    }
    //If chip is still on, button is pressed (Apixel board)
    Serial.println("WARNING: Button pressed ");
    setupMode();
}

// the loop function runs over and over again forever
void loop() {
    if (setupModeStatus) {
        WEB_SERVER.handleClient();
    } else {
        Serial.println("ERROR: Something wrong :-( ");
        blinkLed.red(&led, 200, 1);
        blinkLed.blue(&led, 200, 1);
        blinkLed.green(&led, 200, 1);
    }
}
