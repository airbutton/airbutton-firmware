#include "customurl.h"
#include "setupmode.h"

String get_base_host(){
    String key;
    if (EEPROM.read(0) != 0) {
        // Read custom URL key from eprom
        for (int i = 160; i < 224; ++i) {
            key += char(EEPROM.read(i));
        }
        key = key.c_str();
        Serial.print("Host: ");
        Serial.println(key);
        return key;
    }
}

String get_customurl(){
    String key;
    if (EEPROM.read(0) != 0) {
        // Read custom URL key from eprom
        for (int i = 224; i < 288; ++i) {
            key += char(EEPROM.read(i));
        }
        key = key.c_str();
        Serial.print("Custom URL: ");
        Serial.println(key);
        return key;
    }
}

boolean customurl() {
    String BASE_HOST = get_base_host();
    String CUSTOM_URL = get_customurl();


    Serial.println("Custom URL called");
    // Define the WiFi Client
    WiFiClient client;
    // Make sure we can connect

    if (!client.connect(BASE_HOST.c_str(), 80)) {
        Serial.println("ERROR: Can't connect to host!");
        return false;
    }

    // We now create a URI for the request

    // Build JSON data string
    String value_1 = WiFi.macAddress();
    String value_2 = WiFi.SSID();
    float value_3 = vcc();
    String data = "";
    data = data + "\n" + "{\"value1\":\"" + value_1 + "\",\"value2\":\"" + value_2 + "\",\"value3\":\"" + value_3 + "\"}";
    // Post the button press to Custom URL
    if (client.connect(BASE_HOST.c_str(), 80)) {  // TODO
        // Sent HTTP POST Request with JSON data
        client.println("POST " + CUSTOM_URL + " HTTP/1.1");
        Serial.println("POST " + CUSTOM_URL + " HTTP/1.1");
        blinkLed.blue(&led, 100, 1);
        client.println("Host: " + BASE_HOST);
        Serial.println("Host: " + BASE_HOST);
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

        Serial.println("\n--------IFTTT Response--------");
        while (client.connected()) {
          if (client.available()){
            char response = client.read();
            Serial.print(response);
          }
        }
        Serial.println("\n--------------End-------------");

        blinkLed.blue(&led, 100, 1);
    }
    Serial.println("Custom URL request sent. Goodbye");
    return true;
}

void handleCustomURL(){
    String s = "<h2>Custom URL Settings</h2>\n";
    s += "<form method='get' action='setcustomurl'>\n";
    s += "<label>Host: </label><input value='" + get_base_host() + "' name='BASE_HOST' maxlenght='200'><br>\n";
    s += "<label>Custom URL: </label><input value='" +  get_customurl()+ "' name='CUSTOM_URL' maxlenght='200'><br>\n";
    s += "<br><br><input type='submit' value='Submit'>\n</form>";
    WEB_SERVER.send(200, "text/html", makePage(DEVICE_TITLE,"Custom URL Settings", s));
}

void handleSetCustomURL(){

    wipeConfig(160,288);

    String CUSTOM_URL = urlDecode(WEB_SERVER.arg("CUSTOM_URL"));
    String BASE_HOST = urlDecode(WEB_SERVER.arg("BASE_HOST"));
    Serial.print("Custom URL: ");
    Serial.println(CUSTOM_URL);
    Serial.print("Base Host: ");
    Serial.println(BASE_HOST);

    Serial.println("Writing Custom URL to EEPROM...");
    for (int i = 0; i < BASE_HOST.length(); ++i) {
        EEPROM.write(160 + i, BASE_HOST[i]);
    }

    Serial.println("Writing Custom URL to EEPROM...");
    for (int i = 0; i < CUSTOM_URL.length(); ++i) {
        EEPROM.write(224 + i, CUSTOM_URL[i]);
    }


    EEPROM.commit();
    Serial.println("Custom URL setting write to EEPROM done!");
    String s = "<h1>Custom URL Setup complete.</h1>\n";
    s += "<p>At restart airbutton will try to send data to <br>\n";
    s += "Custom URL: ";
    s += CUSTOM_URL;
    s += " .\n";
    s +="\n<a href='/'>Back</a></p>\n";
    WEB_SERVER.send(200, "text/html", makePage(DEVICE_TITLE, "Write Custom URL Settings", s));
}
