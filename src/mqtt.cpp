#include "mqtt.h"

boolean mqtt() {
    Serial.println("MQTT Button fired");
    String mqtt_server = loadJsonParam("mqtt", "server");
    String mqtt_user = loadJsonParam("mqtt", "user");
    String mqtt_pass = loadJsonParam("mqtt", "pass");
    String mqtt_topic = loadJsonParam("mqtt", "topic");
    mqtt_topic += "/" + DEVICE_TITLE + "/" + CHIP_ID + "/Battery";

    // Define the WiFi and MQTT Client
    WiFiClient wclient;
    PubSubClient client(wclient);

    // Make sure we can connect
    client.setServer(mqtt_server.c_str(),1883);
    if (!client.connect(AP_SSID.c_str(),mqtt_user.c_str(),mqtt_pass.c_str())){
        Serial.println("ERROR: Can't connect to MQTT Broker!");
        return (boolean) false;
    }

    String payload = String(vcc()) + "V";

    // We check that client can connect or print error message
    if (client.state() == MQTT_CONNECTED){
        Serial.println();
        Serial.println("Client connected!");
        client.publish(mqtt_topic.c_str(), payload.c_str(), (boolean) true);
        Serial.print("Sent message ");
        Serial.println(payload);
        Serial.print("to topic ");
        Serial.println(mqtt_topic);
    } else {
        Serial.printf("ERROR: client code %d/n", client.state());
    }

    blinkLed.blue(&led, 100, 1);

    Serial.println("\nMQTT message published. Goodbye");
    return (boolean) true;
}

void handleMQTT() {
    String mqtt_server = loadJsonParam("mqtt", "server");
    String mqtt_user = loadJsonParam("mqtt", "user");
    String mqtt_pass = loadJsonParam("mqtt", "pass");
    String mqtt_topic = loadJsonParam("mqtt", "topic");
    String s = "<h2>MQTT Settings</h2>\n";
    s += "<p>MQTT Client ID: " + AP_SSID + "</p>\n";
    s += "<form method='get' action='setmqtt'>\n";
    s += "<label>MQTT server: <input value='";
    s += mqtt_server;
    s += "' name='server' maxlenght='200'></label><br><br>\n";
    s += "<label>MQTT user: <input value='";
    s += mqtt_user;
    s += "' name='user' maxlenght='200'></label><br><br>\n";
    s += "<label>MQTT user password: <input value='";
    s += mqtt_pass;
    s += "' name='pass' type='password' maxlenght='200'></label><br><br>\n";
    s += "<label>MQTT topic: <input placeholder='ES. MyHome/bedroom' value='" + mqtt_topic;
    s += "' name='topic' maxlenght='200'>/" + DEVICE_TITLE + "/" + CHIP_ID;
    s += "/Battery</label><br><br>\n";
    s += "<br><br><input type='submit' value='Submit'>\n</form>";
    WEB_SERVER.send(200, "text/html", makePage(DEVICE_TITLE,
                                               "MQTT Settings", s));
}

void handleSetMQTT() {
    String mqtt_server = urlDecode(WEB_SERVER.arg("server"));
    Serial.print("MQTT Server: ");
    Serial.println(mqtt_server);

    String mqtt_user = urlDecode(WEB_SERVER.arg("user"));
    Serial.print("MQTT user: ");
    Serial.println(mqtt_user);

    String mqtt_pass = urlDecode(WEB_SERVER.arg("pass"));
    Serial.print("MQTT pass: ");
    Serial.println(mqtt_pass);

    String mqtt_topic = urlDecode(WEB_SERVER.arg("topic"));
    Serial.print("MQTT topic: ");
    Serial.println(mqtt_topic);

    Serial.println("Writing MQTT config to config.json...");
    saveJsonConfig("mqtt", "enabled", (boolean) true);
    saveJsonConfig("mqtt", "server", mqtt_server.c_str());
    saveJsonConfig("mqtt", "user", mqtt_user.c_str());
    saveJsonConfig("mqtt", "pass", mqtt_pass.c_str());
    saveJsonConfig("mqtt", "topic", mqtt_topic.c_str());
    Serial.println("Done!");

    String s = "<h1>MQTT Setup complete.</h1>\n";
    s += "<p>At restart airbutton will try to send data to <br>\n";
    s += "MQTT server <b>";
    s += mqtt_server;
    s += "</b> in topic <b>";
    s += mqtt_topic;
    s += "</b><br>with username <b> \n";
    s += mqtt_user;
    s += "</b> and <b>" + mqtt_pass + "</b> as password.";
    s += "<br><a href='/'>Back</a></p>";
    WEB_SERVER.send(200, "text/html", makePage(DEVICE_TITLE,
                                               "Write MQTT Settings", s));
}
