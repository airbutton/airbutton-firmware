#include "ifttt.h"

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

boolean ifttt() {
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
    float value_3 = vcc();
    String data = "";
    data = data + "\n" + "{\"value1\":\"" + value_1 + "\",\"value2\":\"" + value_2 + "\",\"value3\":\"" + value_3 + "\"}";
    // Post the button press to IFTTT
    if (client.connect(IFTTT_URL, 80)) {
        // Sent HTTP POST Request with JSON data
        client.println("POST " + url + " HTTP/1.1");
        Serial.println("POST " + url + " HTTP/1.1");
        blinkLed.blue(&led, 100, 1);
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
        blinkLed.blue(&led, 100, 1);
    }
    Serial.println("IFTTT request sent. Goodbye");
    return true;
}

void handleIFTTT(){
    String s = "<h2>IFTTT Settings</h2>\n";
    s += "<form method='get' action='setifttt'>\n";
    s += "<label>IFTTT Key: </label><input name='IFTTT_KEY' maxlenght='32'><br>\n";
    s += "<br><label>IFTTT Event: </label><input name='IFTTT_EVENT' maxlenght='32'><br>\n";
    s += "<br><br><input type='submit' value='Submit'>\n</form>";
    WEB_SERVER.send(200, "text/html", makePage(DEVICE_TITLE,"IFTTT Settings", s));
}

void handleSetIFTTT(){

    wipeConfig(96,160);

    String IFTTT_KEY = urlDecode(WEB_SERVER.arg("IFTTT_KEY"));
    Serial.print("IFTTT Key: ");
    Serial.println(IFTTT_KEY);

    String IFTTT_EVENT = urlDecode(WEB_SERVER.arg("IFTTT_EVENT"));
    Serial.print("IFTTT Event: ");
    Serial.println(IFTTT_EVENT);

    Serial.println("Writing IFTTT Key to EEPROM...");
    for (int i = 0; i < IFTTT_KEY.length(); ++i) {
        EEPROM.write(96 + i, IFTTT_KEY[i]);
    }
    Serial.println("Writing IFTTT Event to EEPROM...");
    for (int i = 0; i < IFTTT_EVENT.length(); ++i) {
        EEPROM.write(128 + i, IFTTT_EVENT[i]);
    }
    EEPROM.commit();
    Serial.println("IFTTT settings write to EEPROM done!");
    String s = "<h1>IFTTT Setup complete.</h1>\n";
    s += "<p>At restart airbutton will try to send data to <br>\n";
    s += "IFTTT event: ";
    s += IFTTT_EVENT;
    s += " with key: ";
    s += IFTTT_KEY;
    s += " .\n";
    s +="\n<a href='/'>Back</a></p>\n";
    WEB_SERVER.send(200, "text/html", makePage(DEVICE_TITLE,"Write IFTTT Settings", s));
}
