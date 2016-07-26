#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "utils.h"
#include "config.h"

void handleNotFound() {
    String s = "<h3>Config Mode</h3>\n<p><a href=\"/settings\">Configuration</a></p>";
    WEB_SERVER.send(200, "text/html", makePage(DEVICE_TITLE,"Config mode", s));
}

void handleSettings() {
	String s = "<h2>Wi-Fi Settings</h2>\n";
	s += "<p>Please select the SSID of the network you wish to connect to and then enter the password and submit.</p>\n";
	s += "<form method=\"get\" action=\"setap\">\n";
	s += "<label>SSID: </label>\n<select name=\"ssid\">";
	s += SSID_LIST;
	s += "\n</select>\n";
	s += "<br><br>Password: <input name=\"pass\" length=64 type=\"password\">\n";
	s += "<br><br><input type=\"submit\" value=\"Send\">\n</form>";
    WEB_SERVER.send(200, "text/html", makePage(DEVICE_TITLE,"Wi-Fi Settings", s));
}

void handleSetap() {
	wipeEEPROM();
	for (int i = 0; i < 96; ++i) {
		EEPROM.write(i, 0);
	}
	String ssid = urlDecode(WEB_SERVER.arg("ssid"));
	Serial.print("SSID: ");
	Serial.println(ssid);

	String pass = urlDecode(WEB_SERVER.arg("pass"));
	Serial.print("Password: ");
	Serial.println(pass);

	Serial.println("Writing SSID to EEPROM...");
	for (int i = 0; i < ssid.length(); ++i) {
		EEPROM.write(i, ssid[i]);
	}

	Serial.println("Writing Password to EEPROM...");
	for (int i = 0; i < pass.length(); ++i) {
		EEPROM.write(32 + i, pass[i]);
	}
	EEPROM.commit();
	Serial.println("Write EEPROM done!");
	String s = "<h1>WiFi Setup complete.</h1><p>The button will restart and will try to connected to ";
	s += ssid;
	s += ".";
    WEB_SERVER.send(200, "text/html", makePage(DEVICE_TITLE,"Wi-Fi Settings", s));

	//TODO power off is better
	Serial.println("Rebooting...");
    ESP.restart();
}

#endif
