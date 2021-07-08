#include <Arduino.h>
#include "FS.h"
#include <LITTLEFS.h>
#include <U8g2lib.h>
#include "hpcalc.h"

#define FORMAT_LITTLEFS_IF_FAILED true

U8G2_ST7565_JLX12864_F_4W_SW_SPI u8g2(U8G2_R2, /*clock=*/9, /*data=*/15, /*cs=*/8, /*dc=*/10, /*reset=*/U8X8_PIN_NONE);
//Keyboard_10x4_MCP23016 keyboard(/*MCPAddress=*/0x20, /*MCPSDA=*/D2, /*MCPSCL=*/D1);

DispInterface dispInterface(u8g2);
HPCalc emuInterface(&dispInterface);

void setup() {
    Serial.begin(74880);  // ESP8266 firmware spits out debug info at baud 74880

    if (!LITTLEFS.begin(FORMAT_LITTLEFS_IF_FAILED)) {
        Serial.println("Failed to mount LittleFS");
    }

    emuInterface.init();
    //keyboard.init();
}

void loop() {
    Serial.printf("tick\n");
    emuInterface.tick();
    //emuInterface.processKeypress(keyboard.getKey());
}
