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

void keyboardTick();

void setup() {

    Serial.begin(115200);

    pinMode(34, INPUT);  // CH450 keyboard interrupt (active low)

    if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) {
        Serial.println("Failed to mount SPIFFS");
    }

    setCpuFrequencyMhz(80);  // My devkit has a 40 MHz Xtal crystal
    Serial.printf("CPU Freq: %d MHz\nXtal Freq: %d Mhz\nAPB Freq: %d Hz\n", getCpuFrequencyMhz(), getXtalFrequencyMhz(), getApbFrequency());

    u8g2.begin();
    u8g2.setContrast(224);
    u8g2.setFontMode(1);

    Serial.printf("Keyboard init result: %d\n", keyboard.init());

    //dispInterface.lowBat = true;  //debug
    //dispInterface.displayString("  LOADING");
    emuInterface.init();

    Serial.printf("Initialization completed!\n");
}

void loop() {

    emuInterface.tick();

    if (Serial.available()) {
        int serialInt = Serial.readStringUntil('\n').toInt();
        Serial.printf("Processing serial input: %d\n", serialInt);
        emuInterface.processKeypress(serialInt);
        emuInterface.processKeypress(-1);
    }

    keyboardTick();
    
}

void keyboardTick() {

    //Serial.printf("pin 34 state: %d\n", digitalRead(34));  //debug

    /*
    if (!digitalRead(34)) {
        uint8_t keyData = keyboard.getKeyData();
        uint8_t keycode = keyboard.toKeycode(keyData);
        Serial.printf("\nProcessing keyboard input: \nkeyData: %d\nkeycode: %d\n\n", keyData, keycode);
        emuInterface.processKeypress(keycode);
        emuInterface.processKeypress(-1);
    }
    */

    static bool keyIsDown = false;

    if (!digitalRead(34)) {
        if (keyIsDown) {
            emuInterface.processKeypress(-1);  // should we handle multiple keypresses like this? (CH450 doesn't even support that but I'd like to know anyway.)
        } else {
            keyIsDown = true;
        }
        emuInterface.processKeypress(keyboard.toKeycode(keyboard.getKeyData()));
    }

    if (keyIsDown && !keyboard.toState(keyboard.getKeyData())) {
        emuInterface.processKeypress(-1);
        keyIsDown = false;
    }

}
