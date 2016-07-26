win32 {
    HOMEDIR += $$(USERPROFILE)
}
else {
    HOMEDIR += $$(HOME)
}

INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif/variants/generic"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif/variants/nodemcu"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif/cores/esp8266"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif/cores/esp8266/libb64"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif/cores/esp8266/spiffs"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif/cores/esp8266/umm_malloc"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif/libraries/ESP8266WiFi/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif/libraries/ESP8266WiFi/src/include"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif/libraries/ESP8266WebServer/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif/libraries/ESP8266WebServer/src/detail"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif/libraries/DNSServer/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/lib/Adafruit_NeoPixel_ID28"
INCLUDEPATH += "$${HOMEDIR}/dev/Platformio/gallAButton/lib/ColorBlink/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif/libraries/EEPROM"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif/tools/sdk/include"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif/tools/sdk/lwip/include"
INCLUDEPATH += "$${HOMEDIR}/dev/Platformio/gallAButton/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/lib/Blynk_ID415"
INCLUDEPATH += "$${HOMEDIR}/.platformio/lib/Bounce2_ID1106"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif/libraries/ArduinoOTA"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif/libraries/ESP8266AVRISP/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif/libraries/ESP8266HTTPClient/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif/libraries/ESP8266HTTPUpdateServer/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif/libraries/ESP8266SSDP"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif/libraries/ESP8266WiFiMesh/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif/libraries/ESP8266httpUpdate/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif/libraries/ESP8266mDNS"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif/libraries/Ethernet/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif/libraries/GDBStub/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif/libraries/Hash/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif/libraries/SD/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif/libraries/SPI"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif/libraries/Servo/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif/libraries/SoftwareSerial"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif/libraries/TFT_Touch_Shield_V2"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif/libraries/Ticker"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif/libraries/Wire"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif/libraries/esp8266/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/toolchain-xtensa/xtensa-lx106-elf/include"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/toolchain-xtensa/lib/gcc/xtensa-lx106-elf/4.8.2/include"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/toolchain-xtensa/lib/gcc/xtensa-lx106-elf/4.8.2/include-fixed"

DEFINES += "F_CPU=80000000L"
DEFINES += "__ets__"
DEFINES += "ICACHE_FLASH"
DEFINES += "PLATFORMIO=021101"
DEFINES += "ESP8266"
DEFINES += "ARDUINO_ARCH_ESP8266"
DEFINES += "ARDUINO_ESP8266_ESP12"
DEFINES += "ARDUINO=20300"

OTHER_FILES += platformio.ini

HEADERS += src/config.h
HEADERS += src/ifttt.h
HEADERS += src/setup.h
HEADERS += src/webserver.h
HEADERS += src/utils.h
SOURCES += src/main.cpp
