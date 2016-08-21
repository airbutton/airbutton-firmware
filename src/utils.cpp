#include "utils.h"

boolean loadWiFiSavedConfig() {
    String ssid = ABconfigs.getParam(WIFI_SSID);
    if (ssid == "") {
        return (boolean) false;
    }
    String password = ABconfigs.getParam(WIFI_PSW);
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
    s += "<meta name=\"viewport\" content=\"width=device-width,user-scalable=0\">\n";
    s += "<style>";
    // Simple Reset CSS
    s += "*,*:before,*:after{-webkit-box-sizing:border-box;-moz-box-sizing:border-box;box-sizing:border-box}html{font-size:100%;-ms-text-size-adjust:100%;-webkit-text-size-adjust:100%}html,button,input,select,textarea{font-family:sans-serif}article,aside,details,figcaption,figure,footer,header,hgroup,main,nav,section,summary{display:block}body,form,fieldset,legend,input,select,textarea,button{margin:0}audio,canvas,progress,video{display:inline-block;vertical-align:baseline}audio:not([controls]){display:none;height:0}[hidden],template{display:none}img{border:0}svg:not(:root){overflow:hidden}body{font-family:sans-serif;font-size:16px;font-size:1rem;line-height:22px;line-height:1.375rem;color:#585858;font-weight:400;background:#fff}p{margin:0 0 1em 0}a{color:#cd5c5c;background:transparent;text-decoration:underline}a:active,a:hover{outline:0;text-decoration:none}strong{font-weight:700}em{font-style:italic}";
    // Basic CSS Styles
    s += "body{font-family:sans-serif;font-size:16px;font-size:1rem;line-height:22px;line-height:1.375rem;color:#585858;font-weight:400;background:#fff}p{margin:0 0 1em 0}a{color:#cd5c5c;background:transparent;text-decoration:underline}a:active,a:hover{outline:0;text-decoration:none}strong{font-weight:700}em{font-style:italic}h1{font-size:32px;font-size:2rem;line-height:38px;line-height:2.375rem;margin-top:0.7em;margin-bottom:0.5em;color:#ffffff;font-weight:400}fieldset,legend{border:0;margin:0;padding:0}legend{font-size:18px;font-size:1.125rem;line-height:24px;line-height:1.5rem;font-weight:700}label,button,input,optgroup,select,textarea{color:inherit;font:inherit;margin:0}input{line-height:normal}.input{width:100%}input[type='text'],input[type='email'],input[type='tel'],input[type='date']{height:36px;padding:0 0.4em}input[type='checkbox'],input[type='radio']{box-sizing:border-box;padding:0}";
    // Custom CSS
    s += "header{width:100%;background-color: #decd87;top: 0;min-height:60px;margin-bottom:21px;font-size:15px;color: #fff}.content-body{padding:0 1em 0 1em}header p{font-size: 1.25rem;float: left;position: relative;z-index: 1000;line-height: normal; margin: 15px 0 0 10px} header img{position: relative; top: 4px; left: 6px;}";
    s += "</style>\n";
    s += "<title>";
    s += device_title + page_title;
    s += "</title>\n</head>\n<body>\n";
    s += "<header><img width='166' height='50' title='AIRBUTTON' alt='AIRBUTTON Logo' align='middle' src='data:image/png;base64,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'></header>\n";
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
