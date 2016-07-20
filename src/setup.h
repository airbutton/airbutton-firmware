#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

#include <ColorBlink.h>
#include "config.h"

void handleSettings(){
	WEB_SERVER.send(200, "text/plain", "hello");
}

void handleRoot() {
  WEB_SERVER.send(200, "text/plain", "hello from esp8266!");
}

void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += WEB_SERVER.uri();
  message += "\nMethod: ";
  message += (WEB_SERVER.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += WEB_SERVER.args();
  message += "\n";
  for (uint8_t i=0; i<WEB_SERVER.args(); i++){
    message += " " + WEB_SERVER.argName(i) + ": " + WEB_SERVER.arg(i) + "\n";
  }
  WEB_SERVER.send(404, "text/plain", message);
}

void setupMode() {
	Serial.println("Setup mode started");
	setupModeStatus = true;
	DNSServer DNS_SERVER;

	//WiFI start in client mode
	blinkLed.blue(&led, 500, 1);
	WiFi.mode(WIFI_STA);
	WiFi.disconnect();
	delay(100);
	int n = WiFi.scanNetworks();
	delay(100);

	//Write SSID_LIST in html
	blinkLed.blue(&led, 500, 2);
	Serial.println("");
	for (int i = 0; i < n; ++i) {
		SSID_LIST += "<option value=\"";
		SSID_LIST += WiFi.SSID(i);
		SSID_LIST += "\">";
		SSID_LIST += WiFi.SSID(i);
		SSID_LIST += "</option>";
	}
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
	WEB_SERVER.on("/inline", [](){
	    WEB_SERVER.send(200, "text/plain", "this works as well");
	  });
	WEB_SERVER.on("/", handleRoot);
	WEB_SERVER.onNotFound(handleNotFound);
	WEB_SERVER.begin();
}

