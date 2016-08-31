#include "mqtt.h"

boolean mqtt() {
    Serial.println("MQTT Button fired");
    String mqtt_server = loadJsonParam("mqtt", "server");
    String mqtt_user = loadJsonParam("mqtt", "user");
    String mqtt_pass = loadJsonParam("mqtt", "pass");
    String mqtt_topic = loadJsonParam("mqtt", "topic");

    // Define the WiFi and MQTT Client
    WiFiClient wclient;
    MQTTClient client;

    client.begin(mqtt_server.c_str(), wclient);
    client.subscribe("/example");
  //  client.connect(mqtt_topic.c_str(),mqtt_user.c_str(),mqtt_pass.c_str());
    // publish a message roughly every second.
    for (int i = 1; i < 10; i++) {
        client.publish("/hello", "world");
        blinkLed.blue(&led, 100, 1);
    }
    Serial.println("\nMQTT message published. Goodbye");
    return (boolean) true;
}

void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
    Serial.print("incoming: ");
    Serial.print(topic);
    Serial.print(" - ");
    Serial.print(payload);
    Serial.println();
}

void handleMQTT() {
    String mqtt_server = loadJsonParam("mqtt", "server");
    String mqtt_user = loadJsonParam("mqtt", "user");
    String mqtt_pass = loadJsonParam("mqtt", "pass");
    String mqtt_topic = loadJsonParam("mqtt", "topic");
    String s = "<h2>MQTT Settings</h2>\n";
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
    s += "<label>MQTT topic: <input value='";
    s += mqtt_topic;
    s += "' name='topic' maxlenght='200'></label><br><br>\n";
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
