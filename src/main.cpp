#include <Arduino.h>
#include <EEPROM.h>
#include <Adafruit_NeoPixel.h>

#include <ColorBlink.h>
#include "config.h"
#include "utils.h"
#include "setup.h"

void setup() {
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
    //Check if button is still pressed
    if (buttonStillPressed()){
        Serial.println("WARNING: Button pressed ");
        blinkLed.red(&led, 50, 20);
        setupMode();
        return;
    }
}

// the loop function runs over and over again forever
void loop() {
    if (setupModeStatus) {
        WEB_SERVER.handleClient();
    } else {
        blinkLed.red(&led, 200, 1);
        blinkLed.blue(&led, 200, 1);
        blinkLed.green(&led, 200, 1);
    }
}
