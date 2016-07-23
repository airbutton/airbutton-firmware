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
	String url = "/trigger/" + String(IFTTT_EVENT) + "/with/key/"
			+ String(IFTTT_KEY);
	// Build JSON data string
	String value_1 = WiFi.macAddress();
	String value_2 = WiFi.SSID();
	String value_3 = WiFi.hostname();
	String data = "";
	data = data + "\n" + "{\"value1\":\"" + value_1 + "\",\"value2\":\"" + value_2 + "\",\"value3\":\"" + value_3 + "\"}";
	// Post the button press to IFTTT
	if (client.connect(IFTTT_URL, 80)) {
		// Sent HTTP POST Request with JSON data
		client.println("POST " + url + " HTTP/1.1");
		Serial.println("POST " + url + " HTTP/1.1");
		client.println("Host: " + String(IFTTT_URL));
		Serial.println("Host: " + String(IFTTT_URL));
		client.println("User-Agent: Arduino/1.0");
		Serial.println("User-Agent: Arduino/1.0");
		client.print("Accept: *");
		Serial.print("Accept: *");
		client.print("/");
		Serial.print("/");
		client.println("*");
		Serial.println("*");
		client.print("Content-Length: ");
		Serial.print("Content-Length: ");
		client.println(data.length());
		Serial.println(data.length());
		client.println("Content-Type: application/json");
		Serial.println("Content-Type: application/json");
		client.println("Connection: close");
		Serial.println("Connection: close");
		client.println();
		Serial.println();
		client.println(data);
		Serial.println(data);
	}
	Serial.println("IFTTT request sent. Goodbye");
	return true;
}

#endif