#include <Arduino.h>
#include "FS.h"
#include <SPIFFS.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include "hpcalc.h"

#define FORMAT_SPIFFS_IF_FAILED true

U8G2_ST7565_JLX12864_F_4W_SW_SPI u8g2(U8G2_R2, /*clock=*/18, /*data=*/23, /*cs=*/5, /*dc=*/19, /*reset=*/U8X8_PIN_NONE);
//Keyboard_10x4_MCP23016 keyboard(/*MCPAddress=*/0x20, /*MCPSDA=*/D2, /*MCPSCL=*/D1);

DispInterface dispInterface(u8g2);
HPCalc emuInterface(&dispInterface);

int serialInt;

void setup() {
    Serial.begin(115200);

    if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) {
        Serial.println("Failed to mount SPIFFS");
    }

    u8g2.begin();
    u8g2.setContrast(224);
    u8g2.setFontMode(1);

    //dispInterface.lowBat = true;  //debug
    dispInterface.displayString("LOADING");
    emuInterface.init();
    //keyboard.init();

    Serial.printf("Initialization completed!\n");
}

void loop() {
    emuInterface.tick();
    if (Serial.available()) {
        serialInt = Serial.readStringUntil('\n').toInt();
        Serial.printf("Processing serial input: %d\n", serialInt);
        emuInterface.processKeypress(serialInt);
        emuInterface.processKeypress(-1);
    }
    //emuInterface.processKeypress(keyboard.getKey());
}
