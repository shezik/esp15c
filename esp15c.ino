#include <Arduino.h>
#include "FS.h"
#include <SPIFFS.h>
#include <U8g2lib.h>
#include "hpcalc.h"

#define FORMAT_SPIFFS_IF_FAILED true

U8G2_ST7565_JLX12864_F_4W_SW_SPI u8g2(U8G2_R2, /*clock=*/9, /*data=*/15, /*cs=*/8, /*dc=*/10, /*reset=*/U8X8_PIN_NONE);
//Keyboard_10x4_MCP23016 keyboard(/*MCPAddress=*/0x20, /*MCPSDA=*/D2, /*MCPSCL=*/D1);

DispInterface dispInterface(u8g2);
HPCalc emuInterface(&dispInterface);

void setup() {
    Serial.begin(115200);

    if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) {
        Serial.println("Failed to mount SPIFFS");
    }

    emuInterface.init();
    //keyboard.init();

    Serial.printf("Initialization completed!\n");
}

void loop() {
    emuInterface.tick();
    //emuInterface.processKeypress(keyboard.getKey());
}
