#include "webserver.h"

void handleNotFound() {
    String s = "<h3>Config Mode</h3>\n<p><a href='/settings'>Configuration</a></p>";
    WEB_SERVER.send(200, "text/html", makePage(DEVICE_TITLE,"Config mode", s));
}

void handleSettings() {
    String s = "<h2>Wi-Fi Settings</h2>\n";
    s += "<p>Please select an SSID from the list or add your own.</p>\n";
    s += "<p>Enter the password and submit.</p>\n";
    s += "<form method='get' action='setap'>\n";
    s += "<label>SSID: </label>\n<select name='ssid'>";
    s += SSID_LIST;
    s += "\n</select>\n";
    s += "<br><label>or</label>\n<input name='dssid' maxlength='32' placeholder='SSID'/>\n";
    s += "<br><br><label>Password: </label>\n<input name='pass' maxlength='64' type='password' placeholder='password'>\n";
    s += "<br><br><h2>IFTTT Settings</h2>\n";
    s += "<label>IFTTT Key: </label><input name='IFTTT_KEY' maxlenght='32'><br>\n";
    s += "<br><label>IFTTT Event: </label><input name='IFTTT_EVENT' maxlenght='32'><br>\n";
    s += "<br><br><input type='submit' value='Submit'>\n</form>";
    WEB_SERVER.send(200, "text/html", makePage(DEVICE_TITLE,"Wi-Fi Settings", s));
}

void handleSetap() {
    wipeEEPROM();
    for (int i = 0; i < 160; ++i) {
        EEPROM.write(i, 0);
    }
    String ssid = urlDecode(WEB_SERVER.arg("ssid"));
    Serial.print("SSID: ");
    Serial.println(ssid);

    String dssid = urlDecode(WEB_SERVER.arg("dssid"));
    Serial.print("dSSID: ");
    Serial.println(dssid);

    String pass = urlDecode(WEB_SERVER.arg("pass"));
    Serial.print("Password: ");
    Serial.println(pass);

    String IFTTT_KEY = urlDecode(WEB_SERVER.arg("IFTTT_KEY"));
    Serial.print("IFTTT Key: ");
    Serial.println(IFTTT_KEY);

    String IFTTT_EVENT = urlDecode(WEB_SERVER.arg("IFTTT_EVENT"));
    Serial.print("IFTTT Event: ");
    Serial.println(IFTTT_EVENT);

    Serial.println("Writing SSID to EEPROM...");
    if (dssid == ""){
        for (int i = 0; i < ssid.length(); ++i) {
            EEPROM.write(i, ssid[i]);
        }
    } else {
        for (int i = 0; i < dssid.length(); ++i) {
            EEPROM.write(i, dssid[i]);
        }
    }
    Serial.println("Writing Password to EEPROM...");
    for (int i = 0; i < pass.length(); ++i) {
        EEPROM.write(32 + i, pass[i]);
    }
    Serial.println("Writing IFTTT Key to EEPROM...");
    for (int i = 0; i < IFTTT_KEY.length(); ++i) {
        EEPROM.write(96 + i, IFTTT_KEY[i]);
    }
    Serial.println("Writing IFTTT Event to EEPROM...");
    for (int i = 0; i < IFTTT_EVENT.length(); ++i) {
        EEPROM.write(128 + i, IFTTT_EVENT[i]);
    }
    EEPROM.commit();
    Serial.println("Write EEPROM done!");
    String s = "<h1>WiFi and IFTTT setup complete.</h1><p>The button will restart and will try to connected to ";
    s += ssid;
    s += ".";
    WEB_SERVER.send(200, "text/html", makePage(DEVICE_TITLE,"Wi-Fi Settings", s));

    //TODO power off is better
    Serial.println("Rebooting...");
    ESP.restart();
}
