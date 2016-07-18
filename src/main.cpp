#include <Arduino.h>
#include <EEPROM.h>
#include <Adafruit_NeoPixel.h>

#include <ColorBlink.h>
#include "config.h"
#include "utils.h"

Adafruit_NeoPixel led = Adafruit_NeoPixel(1, RGBPIN, NEO_GRB + NEO_KHZ800);
ColorBlink blinkLed = ColorBlink();

void setup() {
  // Init Serial port
  Serial.begin(115200);
  // Init EEPROM
  EEPROM.begin(512);
  // Init LED
  led.begin();
  led.show();
  blinkLed.green(&led, 100, 20);
}

// the loop function runs over and over again forever
void loop() {
  Serial.println("Loop Init");
  //Check connection
  if (!checkWiFiConnection()){
    Serial.print("ERROR: Connection lost");
    blinkLed.red(&led, 50, 20);
  }

  blinkLed.blue(&led, 50, 10);
  Serial.println("Loop End");
  delay(3000);
};
