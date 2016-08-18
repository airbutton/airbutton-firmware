#ifndef EEPROMCONFIG_H
#define EEPROMCONFIG_H

#include <Arduino.h>
#include <EEPROM.h>

typedef enum {
    //ALL configs
    ALL,
    //WIFI configs
    WIFI,
    WIFI_SSID,
    WIFI_PSW,
    //IFTTT Service
    IFTTT,
    IFTTT_KEY,
    IFTTT_EVENT,
    //Custom Service
    CUSTOM,
    CUSTOM_HOST,
    CUSTOM_URL
} configs;

class EEPROMconfig{
    int wifiParam[3];
    int iftttParam[2];
    int customParam[2];
public:
    EEPROMconfig();
    String getParam(int configs);
    void setParam(int configs, String param);
    void setParam(int configs, String param1, String param2);
    void delParam(int configs);

private:
    int *eepromRange(int configs);
};

#endif // EEPROMCONFIG_H
