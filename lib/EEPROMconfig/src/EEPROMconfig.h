#ifndef EEPROMCONFIG_H
#define EEPROMCONFIG_H

#include <Arduino.h>
#include <EEPROM.h>

typedef enum {
    //ALL configs
    ALL = 1,
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
    CUSTOM_URL,
    //Array dimension
    LAST
} configs;

class EEPROMconfig{

public:
    EEPROMconfig();
    void debugEEPROMrange();
    String getParam(int configs);
    //TODO better overloading here
    void setParam(int configs, String param);
    void setParam(int configs, String param1, String param2);
    void delParam(int configs);

private:
    int *eepromRange(int configs);
    int configStart;
    int paramEnd[LAST];
    int configEnd;
};

#endif // EEPROMCONFIG_H
