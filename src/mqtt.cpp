#include "mqtt.h"

boolean mqtt() {
    Serial.println("MQTT Button fired");
    String mqtt_server = loadJsonParam("mqtt", "server");
    String mqtt_user = loadJsonParam("mqtt", "user");
    String mqtt_pass = loadJsonParam("mqtt", "pass");
    String mqtt_topic = loadJsonParam("mqtt", "topic");

    void callback(const MQTT::Publish &pub) {
        // handle message arrived
    }

    // Define the WiFi Client
    WiFiClient wclient;
    PubSubClient client(wclient, mqtt_server);

    // Make sure we can connect
    if (client.connect(MQTT::Connect("arduinoClient").set_auth(mqtt_user, mqtt_pass))){
        Serial.println("Connected to MQTT server");
    }
}
