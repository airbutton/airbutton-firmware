#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

#include <ColorBlink.h>
#include "config.h"
#include "utils.h"
#include "webserver.h"

void setupMode() {
	Serial.println("Setup mode started");
	setupModeStatus = true;
	DNSServer DNS_SERVER;

	//WiFI start in client mode
	blinkLed.blue(&led, 500, 1);
	WiFi.mode(WIFI_STA);
	WiFi.disconnect();
	delay(200);

	//Write SSID_LIST in html
	blinkLed.blue(&led, 500, 2);
	Serial.println("");
	SSID_LIST = ssidList();
	delay(100);

	//WiFi start in access point mode
	blinkLed.blue(&led, 500, 3);
	WiFi.mode(WIFI_AP);
	WiFi.softAPConfig(AP_IP, AP_IP, IPAddress(255, 255, 255, 0));
	WiFi.softAP(AP_SSID);
	DNS_SERVER.start(53, "*", AP_IP);
	Serial.print("Starting Access Point at ");
	Serial.println(WiFi.softAPIP());

	//TODO
	// Settings Page
	WEB_SERVER.onNotFound(handleNotFound);
	WEB_SERVER.on("/", handleRoot);
	WEB_SERVER.on("/settings", handleSettings);

	WEB_SERVER.begin();
}

