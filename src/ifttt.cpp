#include "ifttt.h"

boolean ifttt() {
    Serial.println("IFTT Button fired");

    const char *ifttt_url = loadJsonParam("ifttt","url");
    String ifttt_key = loadJsonParam("ifttt","key");
    String ifttt_event = loadJsonParam("ifttt","event");

    // Define the WiFi Client
    WiFiClient client;

    // Make sure we can connect
    if (!client.connect(ifttt_url, 80) || ifttt_key == "" || ifttt_event == "") {
        Serial.println("ERROR: Can't connect to IFTTT!");
        return (boolean) false;
    }

    // We now create a URI for the request
    String url = "/trigger/" + ifttt_event + "/with/key/" + ifttt_key;

    // Build JSON data string
    String value_1 = WiFi.macAddress();
    String value_2 = WiFi.SSID();
    String value_3 = String(vcc());
    String data;
    data = data + "\n" + "{\"value1\":\"" + value_1 +
            "\",\"value2\":\"" + value_2 +
            "\",\"value3\":\"" + value_3 +
            "\"}";

    blinkLed.blue(&led, 100, 1);

    Serial.println("======= IFTTT =======");

    String strPayload;
    strPayload += "POST " + url + " HTTP/1.1\r\n";
    strPayload += "Host: " + String(ifttt_url) + "\r\n";
    strPayload += "User-Agent: Arduino/1.0\r\n";
    strPayload += "Connection: close\r\n";
    strPayload += "Accept: */*\r\n";
    strPayload += "Content-Type: application/json\r\n";
    strPayload += "Content-Length: " + String(data.length()) + "\r\n\r\n";
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

    Serial.println("\nIFTTT request sent. Goodbye");
    return (boolean) true;
}

void handleIFTTT() {
    String ifttt_key = loadJsonParam("ifttt","key");
    String ifttt_event = loadJsonParam("ifttt","event");
    String s = "<h2>IFTTT Settings</h2>\n";
    s += "<form method='get' action='setifttt'>\n";
    s += "<label>IFTTT Key: <input value='" + ifttt_key +
            "' name='KEY' maxlenght='200'></label><br>\n";
    s += "<br><label>IFTTT Event: <input value='" + ifttt_event +
            "' name='EVENT' maxlenght='200'></label><br>\n";
    s += "<br><br><input type='submit' value='Submit'>\n</form>";
    WEB_SERVER.send(200, "text/html", makePage(DEVICE_TITLE,
                                               "IFTTT Settings", s));
}

void handleSetIFTTT() {
    String key = urlDecode(WEB_SERVER.arg("KEY"));
    Serial.print("IFTTT Key: ");
    Serial.println(key);

    String event = urlDecode(WEB_SERVER.arg("EVENT"));
    Serial.print("IFTTT Event: ");
    Serial.println(event);

    Serial.println("Writing IFTTT Key and event to config.json...");
    saveJsonConfig("ifttt", "enable", "true");
    saveJsonConfig("ifttt", "url", "maker.ifttt.com");
    saveJsonConfig("ifttt", "key", key.c_str());
    saveJsonConfig("ifttt", "event", event.c_str());
    Serial.println("Done!");

    String s = "<h1>IFTTT Setup complete.</h1>\n";
    s += "<p>At restart airbutton will try to send data to <br>\n";
    s += "IFTTT event: <b>";
    s += event;
    s += "</b> with key: <b>";
    s += key;
    s += "</b>.\n";
    s += "<br><a href='/'>Back</a></p>";
    WEB_SERVER.send(200, "text/html", makePage(DEVICE_TITLE,
                                               "Write IFTTT Settings", s));
}
