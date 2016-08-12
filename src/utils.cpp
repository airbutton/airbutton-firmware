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
    s +="header{width:100%;background-color: #2c3e50;top: 0;min-height:60px;margin-bottom:21px;font-size:15px;color: #fff}.content-body{padding:0 1em 0 1em}header p{font-size: 1.25rem;float: left;position: relative;z-index: 1000;line-height: normal; margin: 15px 0 0 10px} header img{position: relative; top: 4px; left: 6px;}";
    s += "</style>\n";
    s += "<title>";
    s += page_title;
    s += "</title>\n</head>\n<body>\n";
    s += "<header><img width='166' height='50' title='AIRBUTTON' alt='AIRBUTTON Logo' align='middle' src='data:image/png;base64,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'></header>\n";
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
    WiFi.mode(WIFI_OFF);
    digitalWrite(pin, LOW);
}

//Get VCC
float vcc(){
    float vdd;
    vdd = (float)ESP.getVcc() / (float)924;
    return vdd;
}
