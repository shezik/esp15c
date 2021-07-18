#include <Arduino.h>
#include "FS.h"
#include <SPIFFS.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include "hpcalc.h"
#include "Kbd_8x5_CH450.h"

#define FORMAT_SPIFFS_IF_FAILED true

U8G2_ST7565_JLX12864_F_4W_SW_SPI u8g2(U8G2_R2, /*clock=*/18, /*data=*/23, /*cs=*/5, /*dc=*/19, /*reset=*/U8X8_PIN_NONE);
Kbd_8x5_CH450 keyboard(/*sda=*/21, /*scl=*/22, /*freq=*/1000000);

DispInterface dispInterface(u8g2);
HPCalc emuInterface(&dispInterface);

int serialInt;

void setup() {

    Serial.begin(115200);

    pinMode(34, INPUT);  // CH450 interrupt

    if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) {
        Serial.println("Failed to mount SPIFFS");
    }

    u8g2.begin();
    u8g2.setContrast(224);
    u8g2.setFontMode(1);

    keyboard.init();

    //dispInterface.lowBat = true;  //debug
    //dispInterface.displayString("  LOADING");
    emuInterface.init();

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

    /*
    Serial.printf("pin 39 state: %d\n", digitalRead(39));
    Serial.println(keyboard.requestKeyData());
    */

    //if (digitalRead(39)) {
        uint8_t keyData = keyboard.requestKeyData();
        uint8_t keycode = keyboard.toKeycode(keyData);
        Serial.printf("\nProcessing keyboard input: \nkeyData: %d\nkeycode: %d\n\n", keyData, keycode);
        if (keyData & 0b01000000) {
            emuInterface.processKeypress(keycode);
            emuInterface.processKeypress(-1);
        }
    //}

}
