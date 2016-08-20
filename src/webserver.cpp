#include "webserver.h"

void handleNotFound() {
    String s = "<h2>Configuration Mode</h2>\n";
    s += "<p><a href='/wifi'>WiFi</a></p>\n";
    s += "<form method='get' action='reboot'>\n";
    s += "<fieldset>\n<legend>Select services that you want to enable.</legend><br>\n";
    s += "<p><input type='checkbox' name='ifttt' value='true' />&nbsp;&nbsp;&nbsp;<a href='/ifttt'>IFTTT</a></p>\n";
    s += "<p><input type='checkbox' name='custom' value='true' />&nbsp;&nbsp;&nbsp;<a href='/customurl'>Custom URL</a></p><br>\n";
    s += "<p><input type='submit' value='Submit & Reboot' /></p>\n";
    s += "</fieldset>";
    WEB_SERVER.send(200, "text/html", makePage(DEVICE_TITLE,"Configuration mode", s));
}

void handleReboot(){
    String s = "<h2>Rebooting!</h2>\n";
    s += "<p>Services enabled: <p>\n";
    String ifttt = urlDecode(WEB_SERVER.arg("ifttt"));
    String custom = urlDecode(WEB_SERVER.arg("custom"));
    if (ifttt.equals("true")){
    //    ABconfigs.setParam(IFTTT,true);
        Serial.println("IFTTT Enabled");
        s += "<p><b>IFTTT</b><p>\n";
    }
    if (custom.equals("true")){
    //    ABconfigs.setParam(CUSTOM,true);
        Serial.println("CUSTOM URL Enabled");
        s += "<p><b>Custom URL</b><p>\n";
    }
    WEB_SERVER.send(200, "text/html", makePage(DEVICE_TITLE,"Rebooting", s));
    Serial.println("Rebooting...");
    WiFi.mode(WIFI_OFF);
    delay(500);
    ESP.restart();
    //NOTE only the first time after flash Reboot will stuck the chip
}

void handleWiFi() {
    String s = "<h2>Wi-Fi Settings</h2>\n";
    s += "<p>Please select an SSID from the list or add your own.</p>\n";
    s += "<p>Enter the password and submit.</p>\n";
    s += "<form method='get' action='setwifi'>\n";
    s += "<label>SSID: </label>\n<select name='ssid'>";
    s += SSID_LIST;
    s += "\n</select>\n";
    s += "<br><label>or</label>\n<input name='dssid' maxlength='32' placeholder='SSID'/>\n";
    s += "<br><br><label>Password: </label>\n<input name='pass' maxlength='64' type='password' placeholder='password'>\n";
    s += "<br><br><input type='submit' value='Submit'>\n</form>";
    WEB_SERVER.send(200, "text/html", makePage(DEVICE_TITLE,"Wi-Fi Settings", s));
}

void handleSetWiFi() {

    ABconfigs.delParam(WIFI);

    String ssid = urlDecode(WEB_SERVER.arg("ssid"));
    String dssid = urlDecode(WEB_SERVER.arg("dssid"));
    if (!dssid.equals("")){
        ssid = dssid;
    }
    Serial.print("SSID: ");
    Serial.println(ssid);

    String pass = urlDecode(WEB_SERVER.arg("pass"));
    Serial.print("Password: ");
    Serial.println(pass);

    Serial.println("Writing SSID and Password to EEPROM...");
    ABconfigs.setParam(WIFI,ssid,pass);

    Serial.println("WiFi settings write to EEPROM done!");
    String s = "<h1>Wifi Setup complete.</h1>\n";
    s += "<p>At restart airbutton will try to connected to <b>";
    s += ssid;
    s += "</b> net, with <b>";
    s += pass;
    s += "</b> as password.\n";
    s +="<br><a href='/'>Back</a></p>";
    WEB_SERVER.send(200, "text/html", makePage(DEVICE_TITLE,"Write Wi-Fi Settings", s));
}
