#ifndef EEPROMCONFIG_H
#define EEPROMCONFIG_H

#include <Arduino.h>
#include <EEPROM.h>

typedef enum {
    WIFI_SSID,
    WIFI_PSW,
    IFTTT_KEY,
    IFTTT_EVENT,
    CUSTOM_HOST,
    CUSTOM_URL
} configs;

class EEPROMconfig{
    int wifiParam[3];
    int iftttParam[2];
    int customParam[2];
public:
    EEPROMconfig();
    String getparam(int configs);
//    void setparam(int configs, String param);
private:
    int *eepromRange(int configs);
};

#endif // EEPROMCONFIG_H
