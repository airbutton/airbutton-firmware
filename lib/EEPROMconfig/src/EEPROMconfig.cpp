#include <EEPROMconfig.h>

EEPROMconfig::EEPROMconfig(){
    // WIFI 0-10 ssid 0-41 pass 42-105
    // IFTTT 106-115 event 106-147 key 148-179
    // Custom Service 180-189 host 190-253 url 254-317
    configStart = 0;
    paramEnd[WIFI]          = configStart +10;          //10
    paramEnd[WIFI_SSID]     = paramEnd[WIFI] +32;       //42
    paramEnd[WIFI_PSW]      = paramEnd[WIFI_SSID] +64;  //106
    paramEnd[IFTTT]         = paramEnd[WIFI_PSW] +10;   //116
    paramEnd[IFTTT_KEY]     = paramEnd[IFTTT] +32;      //148
    paramEnd[IFTTT_EVENT]   = paramEnd[IFTTT_KEY] +32;  //180
    paramEnd[CUSTOM]        = paramEnd[IFTTT_EVENT] +10;//190
    paramEnd[CUSTOM_HOST]   = paramEnd[CUSTOM] +64;     //254
    paramEnd[CUSTOM_URL]    = paramEnd[CUSTOM_HOST] +64;//318
    configEnd = paramEnd[LAST-1];
}

void EEPROMconfig::debugEEPROMrange(){
    //TODO read and print value
    Serial.println("--------------------------");
    Serial.println("EEPROM range config");
    Serial.printf("configStart = %d\n",configStart);
    String config_name[LAST] = {"ALL",
                                "WIFI","WIFI_SSID","WIFI_PSW",
                                "IFTTT","IFTTT_KEY","IFTTT_EVENT",
                                "CUSTOM","CUSTOM_HOST","CUSTOM_URL",
                                "LAST"};
    for (int i = 1; i < LAST; i++){
        int *range = eepromRange(i);
        Serial.print("paramEnd[" + String(i) + "] = " + paramEnd[i]
                     + "   \t" + config_name[i-1] + "\t" );
        Serial.printf("Start = %d\t",range[0]);
        Serial.printf("\tEnd = %d\n",range[1]);
    }
    Serial.printf("configEnd = %d\n",configEnd);
    Serial.println("--------------------------");
}

int *EEPROMconfig::eepromRange(int configs){
    int *range = new int[2];
    switch (configs) {
    case ALL:
        range[0] = configStart;
        range[1] = configEnd;
        break;
    case WIFI:
        range[0] = paramEnd[WIFI];
        range[1] = paramEnd[WIFI_PSW];
        break;
    case WIFI_SSID:
        range[0] = paramEnd[WIFI];
        range[1] = paramEnd[WIFI_SSID];
        break;
    case WIFI_PSW:
        range[0] = paramEnd[WIFI_SSID];
        range[1] = paramEnd[WIFI_PSW];
        break;
    case IFTTT:
        range[0] = paramEnd[IFTTT];
        range[1] = paramEnd[IFTTT_EVENT];
        break;
    case IFTTT_KEY:
        range[0] = paramEnd[IFTTT];
        range[1] = paramEnd[IFTTT_KEY];
        break;
    case IFTTT_EVENT:
        range[0] = paramEnd[IFTTT_KEY];
        range[1] = paramEnd[IFTTT_EVENT];
        break;
    case CUSTOM:
        range[0] = paramEnd[CUSTOM];
        range[1] = paramEnd[CUSTOM_URL];
        break;
    case CUSTOM_HOST:
        range[0] = paramEnd[CUSTOM];
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

