#include "setupmode.h"

void setupMode() {
    digitalWrite(RETPIN, HIGH);
    Serial.println("Setup mode started");
    setupModeStatus = (boolean) true;

    //WiFI start in client mode
    blinkLed.violet(&led, 100, 1);
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(200);

    //Write SSID_LIST in html
    blinkLed.violet(&led, 100, 1);
    Serial.println("Scan WiFi networks");
    SSID_LIST = ssidList();
    delay(100);

    //WiFi start in access point mode
    blinkLed.violet(&led, 100, 1);
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(AP_IP, AP_IP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(AP_SSID.c_str());
    DNS_SERVER.start(53, "*", AP_IP);
    Serial.print("Starting Access Point at ");
    Serial.println(WiFi.softAPIP());
    if (!MDNS.begin("airbutton")) {
        Serial.println("Error setting up MDNS responder!");
        delay(1000);
    }
    Serial.println("mDNS responder started");
    blinkLed.violet(&led, 100, 2);

    // Settings Page
    WEB_SERVER.on("/wifi.html", handleWiFi);
    WEB_SERVER.on("/ifttt.html", handleIFTTT);
    WEB_SERVER.on("/customurl.html", handleCustomURL);
    WEB_SERVER.on("/mqtt.html",handleMQTT);

    WEB_SERVER.on("/setwifi.html", handleSetWiFi);
    WEB_SERVER.on("/setifttt.html", handleSetIFTTT);
    WEB_SERVER.on("/setcustomurl.html", handleSetCustomURL);
    WEB_SERVER.on("/setmqtt.html", handleSetMQTT);

    WEB_SERVER.on("/reboot.html", handleReboot);
    WEB_SERVER.serveStatic("/css/basic.css",SPIFFS,"/css/basic.css");
    WEB_SERVER.serveStatic("/css/custom.css",SPIFFS,"/css/custom.css");
    WEB_SERVER.serveStatic("/css/simple.css",SPIFFS,"/css/simple.css");
    WEB_SERVER.serveStatic("/img/logo_color_small.png",SPIFFS,"/img/logo_color_small.png");
    WEB_SERVER.onNotFound(handleNotFound);
    WEB_SERVER.begin();
    MDNS.addService("http", "tcp", 80);
    startTime = millis();
}
