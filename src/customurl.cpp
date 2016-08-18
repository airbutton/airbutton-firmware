#include "customurl.h"

boolean customurl() {
    Serial.println("Custom URL called");

    String HOST = ABconfigs.getParam(CUSTOM_HOST);
    String URL = ABconfigs.getParam(CUSTOM_URL);

    // Define the WiFi Client
    WiFiClient client;

    // Make sure we can connect
    if (!client.connect(HOST.c_str(), 80)) {
        Serial.println("ERROR: Can't connect to host!");
        return false;
    }

    // Build JSON data string
    String vMac = WiFi.macAddress();
    String vSid = WiFi.SSID();
    String vVCC = String(vcc());

    String data;
    data = "{\"macaddress\":\"" + vMac + "\",\"ssid\":\"" + vSid + "\",\"vcc\":\"" + vVCC + "\"}";

    blinkLed.blue(&led, 100, 1);

    Serial.println("=== Custom URL ===");

    String strPayload;
    strPayload += "POST " + URL + " HTTP/1.1\r\n";
    strPayload += "Host: " + HOST + "\r\n";
    strPayload += "User-Agent: Arduino/1.0\r\n";
    strPayload += "Connection: close\r\n";
    strPayload += "Content-Type: application/json\r\n";
    strPayload += "Content-Length:" + String(data.length()) + "\r\n\r\n";
    strPayload += data + "\r\n\r\n";

    client.println(strPayload);
    Serial.println(strPayload);

    // Wait for a response
    while (client.connected()) {
        if (client.available()){
            char response = client.read();
            Serial.print(response);
        }
    }

    blinkLed.blue(&led, 100, 1);

    Serial.println("Custom URL request sent. Goodbye");
    return true;
}

void handleCustomURL(){
    String s = "<h2>Custom URL Settings</h2>\n";
    s += "<form method='get' action='setcustomurl'>\n";
    s += "<label>Host: </label><input value='" + ABconfigs.getParam(CUSTOM_HOST) + "' name='HOST' maxlenght='200'><br>\n";
    s += "<label>Custom URL: </label><input value='" +  ABconfigs.getParam(CUSTOM_URL) + "' name='URL' maxlenght='200'><br>\n";
    s += "<br><br><input type='submit' value='Submit'>\n</form>";
    WEB_SERVER.send(200, "text/html", makePage(DEVICE_TITLE,"Custom URL Settings", s));
}

void handleSetCustomURL(){

    ABconfigs.delParam(CUSTOM);

    String URL = urlDecode(WEB_SERVER.arg("URL"));
    String HOST = urlDecode(WEB_SERVER.arg("HOST"));
    Serial.print("Custom URL: ");
    Serial.println(URL);
    Serial.print("Base Host: ");
    Serial.println(HOST);

    Serial.println("Writing Custom URL to EEPROM...");
    for (int i = 0; i < HOST.length(); ++i) {
        EEPROM.write(160 + i, HOST[i]);
    }

    Serial.println("Writing Custom URL to EEPROM...");
    for (int i = 0; i < URL.length(); ++i) {
        EEPROM.write(224 + i, URL[i]);
    }


    EEPROM.commit();
    Serial.println("Custom URL setting write to EEPROM done!");
    String s = "<h1>Custom URL Setup complete.</h1>\n";
    s += "<p>At restart airbutton will try to send data to <br>\n";
    s += "Custom URL: ";
    s += URL;
    s += " .\n";
    s +="\n<a href='/'>Back</a></p>\n";
    WEB_SERVER.send(200, "text/html", makePage(DEVICE_TITLE, "Write Custom URL Settings", s));
}
