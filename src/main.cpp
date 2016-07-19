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
  blinkLed.green(&led, 100, 20);
  //Check connection
  if (!checkWiFiConnection()){
    Serial.print("ERROR: Connection lost");
    blinkLed.red(&led, 50, 20);
    setupMode();
  }
}

// the loop function runs over and over again forever
void loop() {
  Serial.println("Loop Init");
  blinkLed.blue(&led, 50, 10);
  Serial.println("Loop End");
  delay(3000);
};
