#include "utils.h"

boolean loadWiFiSavedConfig() {
    String ssid = loadJsonParam("wifi", "ssid");
    if (ssid == "") {
        return (boolean) false;
    }
    String password = loadJsonParam("wifi", "password");
    if (WiFi.begin(ssid.c_str(), password.c_str())) {
        Serial.print("SSID: ");
        Serial.println(ssid);
        Serial.print("Password: ");
        Serial.println(password);
        return (boolean) true;
    }
    return (boolean) false;
}

// Wi-Fi check connection
boolean checkWiFiConnection() {
    int count = 0;
    Serial.print("Waiting to connect to WiFi network");
    while (count < 20) {
        delay(1000);
        if (WiFi.status() == WL_CONNECTED) {
            Serial.println();
            Serial.println("Connected!");
            blinkLed.green(&led, 100, 3);
            return (boolean) true;
        }
        Serial.print(".");
        blinkLed.blue(&led, 100, 1);
        count++;
    }
    Serial.println("Timed out.");
    blinkLed.red(&led, 100, 3);
    return (boolean) false;
}

// Wi-Fi access point list
String ssidList() {
    String ssid_list;
    int n = WiFi.scanNetworks();
    for (int i = 0; i < n; ++i) {
        ssid_list += "\n<option value=\"";
        ssid_list += WiFi.SSID((uint8_t) i);
        ssid_list += "\">";
        ssid_list += WiFi.SSID((uint8_t) i);
        ssid_list += "</option>";
    }
    return ssid_list;
}

// HTML Page maker
String makePage(String device_title, String page_title, String contents) {
    String s = "<!DOCTYPE html>\n<html>\n<head>\n";
    s += "<meta name='viewport' content='width=device-width,user-scalable=0'>\n";
    s += "<link rel='stylesheet' href='css/simple.css'>\n";
    s += "<link rel='stylesheet' href='css/basic.css'>\n";
    s += "<link rel='stylesheet' href='css/custom.css'>\n";
    s += "<title>";
    s += device_title + " | " + page_title;
    s += "</title>\n</head>\n<body>\n<header>\n";
    s += "<img src='img/logo_color_small.png' title='AIRBUTTON' alt='Airbutton Logo' align='middle'>\n";
    s += "</header>\n<div class=\"content-body\">\n";
    s += contents;
    s += "</div>\n</body>\n</html>";
    return s;
}

// Decode URL
String urlDecode(String input) {
    String s = input;
    s.replace("%20", " ");
    s.replace("+", " ");
    s.replace("%21", "!");
    s.replace("%22", "\"");
    s.replace("%23", "#");
    s.replace("%24", "$");
    s.replace("%25", "%");
    s.replace("%26", "&");
    s.replace("%27", "\'");
    s.replace("%28", "(");
    s.replace("%29", ")");
    s.replace("%30", "*");
    s.replace("%31", "+");
    s.replace("%2C", ",");
    s.replace("%2E", ".");
    s.replace("%2F", "/");
    s.replace("%2C", ",");
    s.replace("%3A", ":");
    s.replace("%3A", ";");
    s.replace("%3C", "<");
    s.replace("%3D", "=");
    s.replace("%3E", ">");
    s.replace("%3F", "?");
    s.replace("%40", "@");
    s.replace("%5B", "[");
    s.replace("%5C", "\\");
    s.replace("%5D", "]");
    s.replace("%5E", "^");
    s.replace("%5F", "-");
    s.replace("%60", "`");
    return s;
}

//Put the board in deepsleep mode
void powerOff() {
    Serial.println("Power OFF");
    WiFi.mode(WIFI_OFF);
    delay(250);
    ESP.deepSleep(0, WAKE_RF_DEFAULT);
}

//Power off APixelBoard
void APixelPowerOff(uint8_t pin) {
    WiFi.mode(WIFI_OFF);
    digitalWrite(pin, LOW);
}

//Get VCC
float vcc() {
    float vdd;
    vdd = (float) ESP.getVcc() / (float) 920;
    return vdd;
}

//Print Json config file for debug
boolean printConfig() {
    File configFile = SPIFFS.open("/config/config.json", "r");
    if (!configFile) {
        Serial.println("Failed to open config file");
        return (boolean) false;
    }
    while (configFile.available()) {
        String line = configFile.readString();
        Serial.println(line);
    }
    configFile.close();
    return (boolean) true;
}

//Load config from Json file in SPIFFS
boolean loadJsonParam(const char *service) {
    File configFile = SPIFFS.open("/config/config.json", "r");
    if (!configFile) {
        Serial.println("ERROR: Failed to open config file (loadJsonParam)");
        return (boolean) false;
    }
    size_t size = configFile.size();
    if (size > 1024) {
        Serial.println("ERROR: Config file size is too large (loadJsonParam)");
        return (boolean) false;
    }
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    DynamicJsonBuffer jsonBuffer;
    JsonObject &json = jsonBuffer.parseObject(buf.get());
    if (!json.success()) {
        Serial.println("ERROR: Failed to parse config file (loadJsonParam)");
        return (boolean) false;
    }
    boolean config = json[service]["enabled"];
    if (config) {
        return (boolean) true;
    }
    return (boolean) false;
}

const char *loadJsonParam(const char *service, const char *param) {
    File configFile = SPIFFS.open("/config/config.json", "r");
    if (!configFile) {
        Serial.println("ERROR: Failed to open config file (loadJsonParam)");
        return (boolean) false;
    }
    size_t size = configFile.size();
    if (size > 1024) {
        Serial.println("ERROR: Config file size is too large (loadJsonParam)");
        return (boolean) false;
    }
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    DynamicJsonBuffer jsonBuffer;
    JsonObject &json = jsonBuffer.parseObject(buf.get());
    if (!json.success()) {
        Serial.println("ERROR: Failed to parse config file (loadJsonParam)");
        return (boolean) false;
    }
    const char *config = json[service][param];
    return (char *) config;
}

//Write config in Json file in SPIFFS
boolean saveJsonConfig(const char *service, const char *param, const char *config) {
    File configFile = SPIFFS.open("/config/config.json", "r");
    if (!configFile) {
        Serial.println("ERROR: Failed to open config file (saveJsonConfig)");
        return (boolean) false;
    }
    size_t size = configFile.size();
    if (size > 1024) {
        Serial.println("ERROR: Config file size is too large (saveJsonConfig)");
        return (boolean) false;
    }
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    DynamicJsonBuffer jsonBuffer;
    JsonObject &json = jsonBuffer.parseObject(buf.get());
    if (!json.success()) {
        Serial.println("ERROR: Failed to parse config file (saveJsonConfig)");
        return (boolean) false;
    }
    configFile.close();
    JsonObject &nested = json[service];
    nested.set(param, config);
    configFile = SPIFFS.open("/config/config.json", "w+");
    json.prettyPrintTo(configFile);
    return (boolean) true;
}

boolean saveJsonConfig(const char *service, const char *param, boolean status) {
    File configFile = SPIFFS.open("/config/config.json", "r");
    if (!configFile) {
        Serial.println("ERROR: Failed to open config file (saveJsonConfig)");
        return (boolean) false;
    }
    size_t size = configFile.size();
    if (size > 1024) {
        Serial.println("ERROR: Config file size is too large (saveJsonConfig)");
        return (boolean) false;
    }
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    DynamicJsonBuffer jsonBuffer;
    JsonObject &json = jsonBuffer.parseObject(buf.get());
    if (!json.success()) {
        Serial.println("ERROR: Failed to parse config file (saveJsonConfig)");
        return (boolean) false;
    }
    configFile.close();
    JsonObject &nested = json[service];
    nested.set(param, status);
    configFile = SPIFFS.open("/config/config.json", "w+");
    json.prettyPrintTo(configFile);
    return (boolean) true;
}

void debugSPIFFS() {
    Dir dir = SPIFFS.openDir("/");
    while (dir.next()) {
        String fileName = dir.fileName();
        Serial.printf("FS File: %s\n", fileName.c_str());
    }

}
