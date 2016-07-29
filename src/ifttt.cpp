#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include <Adafruit_NeoPixel.h>
#include <ColorBlink.h>

String get_ifttt_key(){
    String key;
    if (EEPROM.read(0) != 0) {
        //IFTTT Key
        for (int i = 96; i < 128; ++i) {
            key += char(EEPROM.read(i));
        }
        key = key.c_str();
        Serial.print("IFTTT Key: ");
        Serial.println(key);
        return key;
    }
}

String get_ifttt_event(){
    String event;
    if (EEPROM.read(0) != 0) {
        //IFTTT Key
        for (int i = 128; i < 160; ++i) {
            event += char(EEPROM.read(i));
        }
        event = event.c_str();
        Serial.print("IFTTT event: ");
        Serial.println(event);
        return event;
    }
}

boolean ifttt(Adafruit_NeoPixel *led,ColorBlink *blinkLed) {
    const char* IFTTT_URL= "maker.ifttt.com";
    String IFTTT_KEY = get_ifttt_key();
    String IFTTT_EVENT = get_ifttt_event();
    Serial.println("IFTT Button fired");
    // Define the WiFi Client
    WiFiClient client;
    // Make sure we can connect
    if (!client.connect(IFTTT_URL, 80)) {
        Serial.println("ERROR: Can't connect to IFTTT!");
        return false;
    }
    // We now create a URI for the request
    String url = "/trigger/" + IFTTT_EVENT + "/with/key/" + IFTTT_KEY;
    // Build JSON data string
    String value_1 = WiFi.macAddress();
    String value_2 = WiFi.SSID();
    String value_3 = WiFi.hostname();
    String data = "";
    data = data + "\n" + "{\"value1\":\"" + value_1 + "\",\"value2\":\"" + value_2 + "\",\"value3\":\"" + value_3 + "\"}";
    // Post the button press to IFTTT
    if (client.connect(IFTTT_URL, 80)) {
        // Sent HTTP POST Request with JSON data
        client.println("POST " + url + " HTTP/1.1");
        Serial.println("POST " + url + " HTTP/1.1");
        blinkLed->blue(led, 10, 5);
        client.println("Host: " + String(IFTTT_URL));
        Serial.println("Host: " + String(IFTTT_URL));
        client.println("User-Agent: Arduino/1.0");
        Serial.println("User-Agent: Arduino/1.0");
        client.print("Accept: *");
        Serial.print("Accept: *");
        client.print("/");
        Serial.print("/");
        client.println("*");
        Serial.println("*");
        client.print("Content-Length: ");
        Serial.print("Content-Length: ");
        client.println(data.length());
        Serial.println(data.length());
        client.println("Content-Type: application/json");
        Serial.println("Content-Type: application/json");
        client.println("Connection: close");
        Serial.println("Connection: close");
        client.println();
        client.println(data);
        Serial.println(data);
        blinkLed->blue(led, 10, 5);
    }
    Serial.println("IFTTT request sent. Goodbye");
    return true;
}