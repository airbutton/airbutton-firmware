#include <EEPROMconfig.h>

EEPROMconfig::EEPROMconfig(){
    // WIFI
    // ssid 0-31 pass 32-95
    // IFTTT
    // event 96-128 key 128-159
    // Custom Service
    // host 160-224 url 224-287
    configStart = 0;
    paramEnd[WIFI_SSID] = configStart + 32;             //32
    paramEnd[WIFI_PSW]  = paramEnd[WIFI_SSID] + 64;     //96
    paramEnd[IFTTT_KEY] = paramEnd[WIFI_PSW] +32;       //128
    paramEnd[IFTTT_EVENT]   = paramEnd[IFTTT_KEY] +32;  //160
    paramEnd[CUSTOM_HOST]   = paramEnd[IFTTT_EVENT] +64;//224
    paramEnd[CUSTOM_URL]    = paramEnd[CUSTOM_HOST] +64;//288
    configEnd = paramEnd[LAST-1];
}

int *EEPROMconfig::eepromRange(int configs){
    int *range = new int[2];
    switch (configs) {
    case ALL:
        range[0] = configStart;
        range[1] = configEnd;
        break;
    case WIFI:
        range[0] = configStart;
        range[1] = paramEnd[WIFI_PSW];
        break;
    case WIFI_SSID:
        range[0] = configStart;
        range[1] = paramEnd[WIFI_SSID];
        break;
    case WIFI_PSW:
        range[0] = paramEnd[WIFI_SSID];
        range[1] = paramEnd[WIFI_PSW];
        break;
    case IFTTT:
        range[0] = paramEnd[WIFI_PSW];
        range[1] = paramEnd[IFTTT_EVENT];
        break;
    case IFTTT_KEY:
        range[0] = paramEnd[WIFI_PSW];
        range[1] = paramEnd[IFTTT_KEY];
        break;
    case IFTTT_EVENT:
        range[0] = paramEnd[IFTTT_KEY];
        range[1] = paramEnd[IFTTT_EVENT];
        break;
    case CUSTOM:
        range[0] = paramEnd[IFTTT_EVENT];
        range[1] = paramEnd[CUSTOM_URL];
        break;
    case CUSTOM_HOST:
        range[0] = paramEnd[IFTTT_EVENT];
        range[1] = paramEnd[CUSTOM_HOST];
        break;
    case CUSTOM_URL:
        range[0] = paramEnd[CUSTOM_HOST];
        range[1] = paramEnd[CUSTOM_URL];
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

