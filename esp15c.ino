#include <Arduino.h>
#include "Keyboard_10x4_MCP23016.h"
#include <ESP8266WiFi.h>
//#include <Wire.h>
//#include <LittleFS.h>
#include <U8g2lib.h>
#include "hpcalc.h"

U8G2_ST7565_JLX12864_F_4W_SW_SPI u8g2(U8G2_R2, /*clock=*/D5, /*data=*/D7, /*cs=*/D8, /*dc=*/D6, /*reset=*/U8X8_PIN_NONE);
Keyboard_10x4_MCP23016 keyboard(/*MCPAddress=*/0x20, /*MCPSDA=*/D2, /*MCPSCL=*/D1);

DispInterface *dispInterface(u8g2);
HPCalc emuInterface(dispInterface);

void setup() {
    // Disable unused WLAN to reduce power consumption
    WiFi.disconnect();
    WiFi.mode(WIFI_OFF);
    WiFi.forceSleepBegin();

    Serial.begin(74880);  // ESP8266 firmware spits out debug info at baud 74880

    emuInterface.init();

    keyboard.init();
}

void loop() {
    emuInterface.tick();
    emuInterface.processKeypress(keyboard.getKey());
}
