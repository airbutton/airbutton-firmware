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
        return (boolean) false;
    }

    // Build JSON data string
    String vMac = WiFi.macAddress();
    String vSid = WiFi.SSID();
    String vVCC = String(vcc());

    String data;
    data = "{\"macaddress\":\"" + vMac +
            "\",\"ssid\":\"" + vSid +
            "\",\"vcc\":\"" + vVCC + "\"}";

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
        if (client.available()) {
            char response = (char) client.read();
            Serial.print(response);
        }
    }

    blinkLed.blue(&led, 100, 1);

    Serial.println("\nCustom URL request sent. Goodbye");
    return (boolean) true;
}

void handleCustomURL() {
    String s = "<h2>Custom URL Settings</h2>\n";
    s += "<form method='get' action='setcustomurl'>\n";
    s += "<label>Host: <input value='" +
            ABconfigs.getParam(CUSTOM_HOST) +
            "' name='HOST' maxlenght='200'></label><br>\n";
    s += "<label>Custom URL: <input value='" +
            ABconfigs.getParam(CUSTOM_URL) +
            "' name='URL' maxlenght='200'></label><br>\n";
    s += "<br><br><input type='submit' value='Submit'>\n</form>";
    WEB_SERVER.send(200, "text/html",
                    makePage(DEVICE_TITLE, "Custom URL Settings", s));
}

void handleSetCustomURL() {

    ABconfigs.delParam(CUSTOM);

    String HOST = urlDecode(WEB_SERVER.arg("HOST"));
    Serial.print("Base Host: ");
    Serial.println(HOST);

    String URL = urlDecode(WEB_SERVER.arg("URL"));
    Serial.print("Custom URL: ");
    Serial.println(URL);

    Serial.println("Writing Custom HOST and URL to EEPROM...");
    ABconfigs.setParam(CUSTOM, HOST, URL);

    Serial.println("Custom URL setting write to EEPROM done!");
    String s = "<h1>Custom URL Setup complete.</h1>\n";
    s += "<p>At restart airbutton will try to send data to <br>\n";
    s += "Custom URL: <b>";
    s += HOST + URL;
    s += "</b>.\n";
    s += "<br><a href='/'>Back</a></p>";
    WEB_SERVER.send(200, "text/html", makePage(DEVICE_TITLE,
                                               "Write Custom URL Settings", s));
}
