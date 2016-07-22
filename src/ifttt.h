/*
 * IFTTT.h
 *
 *  Created on: 22 lug 2016
 *      Author: gallochri
 */

#ifndef IFTTT_H
#define IFTTT_H

#include "config.h"

boolean ifttt() {
	Serial.println("IFTT Button fired");
	// Define the WiFi Client
	WiFiClient client;
	// Make sure we can connect
	if (!client.connect(IFTTT_URL, 80)) {
		Serial.println("ERROR: Can't connect to IFTTT!");
		return false;
	}
	// We now create a URI for the request
	String url = "/trigger/" + String(IFTTT_EVENT) + "/with/key/" + String(IFTTT_KEY);
	// Post the button press to IFTTT
	if (client.connect(IFTTT_URL, 80)) {
		// Sent HTTP POST Request with JSON data
		client.println("GET " + url + " HTTP/1.1");
		Serial.println("GET " + url + " HTTP/1.1");
		client.println("Host: " + String(IFTTT_URL));
		Serial.println("Host: " + String(IFTTT_URL));
		client.print("Accept: *");
		Serial.print("Accept: *");
		client.print("/");
		Serial.print("/");
		client.println("*");
		Serial.println("*");
		client.println("User-Agent: Mozilla/4.0 (compatible; esp8266 Lua; Windows NT 5.1)");
		Serial.println("User-Agent: Mozilla/4.0 (compatible; esp8266 Lua; Windows NT 5.1)");
	}
	Serial.println("IFTTT request sent. Goodbye");
	return true;
}

#endif
