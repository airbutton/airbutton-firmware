#include <Arduino.h>
#include <EEPROM.h>
#include <Adafruit_NeoPixel.h>

#include <ColorBlink.h>
#include "config.h"
#include "utils.h"
#include "setup.h"
#include "ifttt.h"

void setup() {
	//Set GPIO4 to HIGH
	pinMode(RETPIN, OUTPUT);
	digitalWrite(RETPIN, HIGH);
    // Init Serial port
    Serial.begin(115200);
    // Init EEPROM
    EEPROM.begin(512);
    // Init LED
    led.begin();
    led.show();
    blinkLed.green(&led, 50, 20);

    //Try to connect with saved config
    if (!loadWiFiSavedConfig()){
        Serial.println("WARNING: WiFi configuration not found");
        blinkLed.red(&led, 50, 20);
        setupMode();
        return;
    }
    //Check connection
    if (!checkWiFiConnection()) {
        Serial.println("ERROR: Connection lost");
        blinkLed.red(&led, 50, 20);
        setupMode();
        return;
    }
    //Button is connected! try to call to IFTTT
    for (int i = 0; i < 3; i++) {
    	if (ifttt()){
    		Serial.println("Success!");
    		blinkLed.green(&led, 50, 20);
    		break;
    	} else {
    		Serial.println("WARNING: IFTTT failed! attempt nr " + i);
    		blinkLed.red(&led, 50, 20);
    	}
    }

    //Check if button is still pressed
    if (buttonStillPressed()){
        Serial.println("WARNING: Button pressed ");
        blinkLed.red(&led, 50, 20);
        setupMode();
        return;
    }
    //TODO Deep sleep mode
    //power off
    digitalWrite(RETPIN, LOW);
    ESP.restart();
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
