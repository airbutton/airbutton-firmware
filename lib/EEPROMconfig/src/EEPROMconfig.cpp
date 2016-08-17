#include <EEPROMconfig.h>

EEPROMconfig::EEPROMconfig(){
    wifiParam[0] = 0;                   //Init WiFi SSID (default 0)
    wifiParam[1] = wifiParam[0]+32;     //End SSID, init WiFi Password (default 32)
    wifiParam[2] = wifiParam[1]+64;     //End Wifi,init IFTTT event (default 96)
    iftttParam[0] = wifiParam[2]+32;    //End IFTTT event, init IFTTT key (default 128)
    iftttParam[1] = iftttParam[0]+32;   //End IFTTT, init custom host (default 160)
    customParam[0] = iftttParam[1]+64;  //End custom host, init custom url (default 224)
    customParam[1] = customParam[0]+64; //End custom url (default 288)
}

int *EEPROMconfig::eepromRange(int configs){
    int *range = new int[2];
    switch (configs) {
    case WIFI_SSID:
        range[0] = wifiParam[0];
        range[1] = wifiParam[1];
        break;
    case WIFI_PSW:
        range[0] = wifiParam[1];
        range[1] = wifiParam[2];
        break;
    case IFTTT_EVENT:
        range[0] = wifiParam[2];
        range[1] = iftttParam[0];
        break;
    case IFTTT_KEY:
        range[0] = iftttParam[0];
        range[1] = iftttParam[1];
        break;
    case CUSTOM_HOST:
        range[0] = iftttParam[1];
        range[1] = customParam[0];
        break;
    case CUSTOM_URL:
        range[0] = customParam[0];
        range[1] = customParam[1];
        break;
    default:
        break;
    }
    return range;
}

String EEPROMconfig::getparam(int configs){
    int *range=eepromRange(configs);
    String param = "";
    if (EEPROM.read(0) != 0) {
        for ( int i = range[0]; i < range[1]; ++i){
            param += char(EEPROM.read(i));
        }
        param = param.c_str();
    }
        return param;
}

