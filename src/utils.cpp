#include <Arduino.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Adafruit_NeoPixel.h>
#include <ColorBlink.h>

// Load WiFi configuration from EEPROM
boolean loadWiFiSavedConfig() {
    String ssid;
    String password;
    String IFTTT_KEY;
    String IFTTT_EVENT;
    Serial.println("\nReading Saved Config....");
    if (EEPROM.read(0) != 0) {
        //WiFi SSID
        for (int i = 0; i < 32; ++i) {
            ssid += char(EEPROM.read(i));
        }
        ssid = ssid.c_str();
        Serial.print("SSID: ");
        Serial.println(ssid);
        //WiFi Password
        for (int i = 32; i < 96; ++i) {
            password += char(EEPROM.read(i));
        }
        password = password.c_str();
        Serial.print("Password: ");
        Serial.println(password);
        //IFTTT Key
        for (int i = 96; i < 128; ++i) {
            IFTTT_KEY += char(EEPROM.read(i));
        }
        IFTTT_KEY = IFTTT_KEY.c_str();
        Serial.print("IFTTT Key: ");
        Serial.println(IFTTT_KEY);
        //IFTTT Event
        for (int i = 128; i < 160; ++i) {
            IFTTT_EVENT += char(EEPROM.read(i));
        }
        IFTTT_EVENT = IFTTT_EVENT.c_str();
        Serial.print("IFTTT Event: ");
        Serial.println(IFTTT_EVENT);
        //Wifi Connect
        WiFi.begin(ssid.c_str(), password.c_str());
        return true;
    } else {
        Serial.println("Saved Configuration not found.");
        return false;
    }
}

// Wi-Fi check connection
boolean checkWiFiConnection(Adafruit_NeoPixel *led,ColorBlink *blinkLed) {
    int count = 0;
    Serial.print("Waiting to connect to WiFi network");
    while (count < 20) {
        if (WiFi.status() == WL_CONNECTED) {
            Serial.println();
            Serial.println("Connected!");
            blinkLed->green(led, 300, 2);
            return true;
        }
        delay(100);
        Serial.print(".");
        blinkLed->blue(led, 100, 1);
        count++;
    }
    Serial.println("Timed out.");
    blinkLed->red(led, 300, 2);
    return false;
}

// Wi-Fi access point list
String ssidList() {
    int n = WiFi.scanNetworks();
    String SSID_LIST = "";
    for (int i = 0; i < n; ++i) {
        SSID_LIST += "\n<option value=\"";
        SSID_LIST += WiFi.SSID(i);
        SSID_LIST += "\">";
        SSID_LIST += WiFi.SSID(i);
        SSID_LIST += "</option>";
    }
    return SSID_LIST;
}

// HTML Page maker
String makePage(String DEVICE_TITLE,String title, String contents) {
    String s = "<!DOCTYPE html>\n<html>\n<head>\n";
    s += "<meta name=\"viewport\" content=\"width=device-width,user-scalable=0\">\n";
    s += "<style>";
    // Simple Reset CSS
    s += "*,*:before,*:after{-webkit-box-sizing:border-box;-moz-box-sizing:border-box;box-sizing:border-box}html{font-size:100%;-ms-text-size-adjust:100%;-webkit-text-size-adjust:100%}html,button,input,select,textarea{font-family:sans-serif}article,aside,details,figcaption,figure,footer,header,hgroup,main,nav,section,summary{display:block}body,form,fieldset,legend,input,select,textarea,button{margin:0}audio,canvas,progress,video{display:inline-block;vertical-align:baseline}audio:not([controls]){display:none;height:0}[hidden],template{display:none}img{border:0}svg:not(:root){overflow:hidden}body{font-family:sans-serif;font-size:16px;font-size:1rem;line-height:22px;line-height:1.375rem;color:#585858;font-weight:400;background:#fff}p{margin:0 0 1em 0}a{color:#cd5c5c;background:transparent;text-decoration:underline}a:active,a:hover{outline:0;text-decoration:none}strong{font-weight:700}em{font-style:italic}";
    // Basic CSS Styles
    s +="body{font-family:sans-serif;font-size:16px;font-size:1rem;line-height:22px;line-height:1.375rem;color:#585858;font-weight:400;background:#fff}p{margin:0 0 1em 0}a{color:#cd5c5c;background:transparent;text-decoration:underline}a:active,a:hover{outline:0;text-decoration:none}strong{font-weight:700}em{font-style:italic}h1{font-size:32px;font-size:2rem;line-height:38px;line-height:2.375rem;margin-top:0.7em;margin-bottom:0.5em;color:#ffffff;font-weight:400}fieldset,legend{border:0;margin:0;padding:0}legend{font-size:18px;font-size:1.125rem;line-height:24px;line-height:1.5rem;font-weight:700}label,button,input,optgroup,select,textarea{color:inherit;font:inherit;margin:0}input{line-height:normal}.input{width:100%}input[type='text'],input[type='email'],input[type='tel'],input[type='date']{height:36px;padding:0 0.4em}input[type='checkbox'],input[type='radio']{box-sizing:border-box;padding:0}";
    // Custom CSS
    s +="header{width:100%;background-color: #2c3e50;top: 0;min-height:60px;margin-bottom:21px;font-size:15px;color: #fff}.content-body{padding:0 1em 0 1em}header p{font-size: 1.25rem;float: left;position: relative;z-index: 1000;line-height: normal; margin: 15px 0 0 10px}";
    s += "</style>\n";
    s += "<title>";
    s += title;
    s += "</title>\n</head>\n<body>\n";
    s += "<header><h1>" + DEVICE_TITLE + "</h1></header>\n";
    s += "<div class=\"content-body\">\n";
    s += contents;
    s += "\n</div>\n";
    s += "</body>\n</html>";
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

// Wipe EEPROM
void wipeEEPROM() {
    EEPROM.begin(512);
    // write a 0 to all 512 bytes of the EEPROM
    for (int i = 0; i < 512; i++)
        EEPROM.write(i, 0);
    EEPROM.end();
    EEPROM.begin(512);
}
