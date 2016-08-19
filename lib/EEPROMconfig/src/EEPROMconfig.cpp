#include <EEPROMconfig.h>

EEPROMconfig::EEPROMconfig(){
    // WIFI
    // ssid 0-31 pass 32-95
    // IFTTT
    // event 96-128 key 128-159
    // Custom Service
    // host 160-224 url 224-287
    wifiParam[0] = 0;                   // 0
    wifiParam[1] = wifiParam[0]+32;     // 32
    wifiParam[2] = wifiParam[1]+64;     // 96
    iftttParam[0] = wifiParam[2]+32;    // 128
    iftttParam[1] = iftttParam[0]+32;   // 160
    customParam[0] = iftttParam[1]+64;  // 224
    customParam[1] = customParam[0]+64; // 288
}

int *EEPROMconfig::eepromRange(int configs){
    int *range = new int[2];
    switch (configs) {
    case ALL:
        range[0] = wifiParam[0];
        range[1] = customParam[1];
        break;
    case WIFI:
        range[0] = wifiParam[0];
        range[1] = wifiParam[2];
        break;
    case WIFI_SSID:
        range[0] = wifiParam[0];
        range[1] = wifiParam[1];
        break;
    case WIFI_PSW:
        range[0] = wifiParam[1];
        range[1] = wifiParam[2];
        break;
    case IFTTT:
        range[0] = wifiParam[2];
        range[1] = iftttParam[1];
        break;
    case IFTTT_KEY:
        range[0] = wifiParam[2];
        range[1] = iftttParam[0];
        break;
    case IFTTT_EVENT:
        range[0] = iftttParam[0];
        range[1] = iftttParam[1];
        break;
    case CUSTOM:
        range[0] = iftttParam[1];
        range[1] = customParam[1];
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

String EEPROMconfig::getParam(int configs){
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

void EEPROMconfig::setParam(int configs, String param){
    int *range=eepromRange(configs);
    for (int i = 0; i < param.length(); ++i){
        EEPROM.write(range[0] + i, param[i]);
    }
    EEPROM.commit();
}

void EEPROMconfig::setParam(int configs, String par1, String par2){
    int *range1=eepromRange(configs+1);
    int *range2=eepromRange(configs+2);
    for (int i = 0; i < par1.length(); ++i){
        EEPROM.write(range1[0] + i, par1[i]);
    }
    for (int i = 0; i < par2.length(); ++i){
        EEPROM.write(range2[0] + i, par2[i]);
    }
    EEPROM.commit();
}

void EEPROMconfig::delParam(int configs){
    int *range=eepromRange(configs);
    EEPROM.begin(512);
    for (int i = range[0]; i < range[1]; ++i){
        EEPROM.write(i, 0);
    }
    EEPROM.end();
    EEPROM.begin(512);
}

