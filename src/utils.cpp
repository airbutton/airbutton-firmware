#include "utils.h"

// Load WiFi configuration from EEPROM
String get_ssid(){
    String ssid;
    if (EEPROM.read(0) != 0) {
        //WiFi SSID
        for (int i = 0; i < 32; ++i){
            ssid += char(EEPROM.read(i));
        }
        ssid = ssid.c_str();
        return ssid;
    }
    Serial.println("ERROR: SSID not found");
    return "";
}

String get_wifi_pwd(){
    String wifi_pwd;
    if (EEPROM.read(32) != 0){
        //WiFi Password
        for (int i = 32; i < 96; ++i) {
            wifi_pwd += char(EEPROM.read(i));
        }
        wifi_pwd = wifi_pwd.c_str();
        return wifi_pwd;
    }
    Serial.println("WARNING: empty WiFi password");
    return wifi_pwd;
}

boolean loadWiFiSavedConfig() {
    String ssid = get_ssid();
    if (ssid == ""){
        return false;
    }
    String password = get_wifi_pwd();
    if (WiFi.begin(ssid.c_str(), password.c_str())){
        Serial.print("SSID: ");
        Serial.println(ssid);
        Serial.print("Password: ");
        Serial.println(password);
        return true;
    }
    return false;
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
            return true;
        }
        Serial.print(".");
        blinkLed.blue(&led, 100, 1);
        count++;
    }
    Serial.println("Timed out.");
    blinkLed.red(&led, 100, 3);
    return false;
}

// Wi-Fi access point list
String ssidList() {
    String ssid_list;
    int n = WiFi.scanNetworks();
    for (int i = 0; i < n; ++i) {
        ssid_list += "\n<option value=\"";
        ssid_list += WiFi.SSID(i);
        ssid_list += "\">";
        ssid_list += WiFi.SSID(i);
        ssid_list += "</option>";
    }
    return ssid_list;
}

// HTML Page maker
String makePage(String device_title,String page_title, String contents) {
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
    s += page_title;
    s += "</title>\n</head>\n<body>\n";
    s += "<header><h1>" + device_title + "</h1></header>\n";
    s += "<div class=\"content-body\">\n";
    s += contents;
    s += "\n</div>\n";
    s += "</body>\n</html>";
    return s;
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

// Wipe only specific config
// WIFI
// ssid 0-32 pass 32-96
// IFTTT
// event 96-128 key 128-160
void wipeConfig(int start, int end) {
    EEPROM.begin(512);
    for (int i = start; i < end; i++)
        EEPROM.write(i, 0);
    EEPROM.end();
    EEPROM.begin(512);
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
void APixelPowerOff(uint8_t pin){
    digitalWrite(pin, LOW);
}
