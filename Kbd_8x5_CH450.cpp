#include "Kbd_8x5_CH450.h"

Kbd_8x5_CH450::Kbd_8x5_CH450(uint8_t sda_, uint8_t scl_, unsigned int freq_)
    : sda(sda_)
    , scl(scl_)
    , freq(freq_)
{
    // do nothing
}

void Kbd_8x5_CH450::startComm() {
    //Serial.printf("Going into %s!\n", __func__); //debug
    digitalWrite(sda, HIGH);
    delay(10);
    digitalWrite(scl, HIGH);
    delay(10);
    digitalWrite(sda, LOW);
    delay(10);
    digitalWrite(scl, LOW);
    delay(10);
}

void Kbd_8x5_CH450::stopComm() {
    //Serial.printf("Going into %s!\n", __func__); //debug
    //digitalWrite(scl, LOW);
    //delay(10);
    digitalWrite(sda, LOW);
    delay(10);
    digitalWrite(scl, HIGH);  // stays high during inactive?
    delay(10);
    digitalWrite(sda, HIGH);
    delay(10);
}

bool Kbd_8x5_CH450::writeByte(uint8_t data) {
    //Serial.printf("Going into %s!\n", __func__); //debug
    for (int8_t i = 7; i > -1; i--) {
        if (data & (1 << i)) {
            digitalWrite(sda, HIGH);
        } else {
            digitalWrite(sda, LOW);
        }
        delay(10);
        digitalWrite(scl, HIGH);
        delay(10);
        digitalWrite(scl, LOW);
        delay(10);
    }
    pinMode(sda, INPUT);
    digitalWrite(scl, HIGH);
    delay(10);
    bool result = digitalRead(sda);
    delay(10);
    digitalWrite(scl, LOW);
    pinMode(sda, OUTPUT);  // terminal state: sda = low, scl = low
    //Serial.printf("writeByte result is %d\n", result); //debug
    return result;
}

uint8_t Kbd_8x5_CH450::readByte() {
    //Serial.printf("Going into %s!\n", __func__); //debug
    uint8_t data = 0;
    pinMode(sda, INPUT);
    for (int8_t i = 7; i > -1; i--) {
        digitalWrite(scl, HIGH);
        delay(10);
        if (digitalRead(sda)) {
            //Serial.println("We've got something"); //debug
            data |= (1 << i);
        }
        digitalWrite(scl, LOW);
        delay(10);
    }
    pinMode(sda, OUTPUT);
    digitalWrite(sda, HIGH);
    delay(10);
    digitalWrite(scl, HIGH);
    delay(10);
    digitalWrite(scl, LOW);
    delay(10);
    return data;
}

bool Kbd_8x5_CH450::init() {
    //Serial.printf("Going into %s!\n", __func__); //debug

    pinMode(sda, OUTPUT);  // Always change pinMode back to OUTPUT state after fiddling 
    pinMode(scl, OUTPUT);  // with it (changing its mode). We assume it is at OUTPUT state by default.
    
    startComm();
    bool resultA = writeByte(0b01001000);  // magic byte to change settings
    bool resultB = writeByte(0b00000010);  // 0: disable sleep; 00: full intensity (useless here);
                                           // 000: separator; 1: enable keyboard scanner; 0: disable LED segments driver
    stopComm();
    
    return resultA && resultB;

}

uint8_t Kbd_8x5_CH450::requestKeyData() {
    //Serial.printf("Going into %s!\n", __func__); //debug
    startComm();
    bool resultA = writeByte(0b01001111);  // magic byte to request key data
    uint8_t resultB = readByte();
    stopComm();
    delay(100);
    return resultA ? resultB : 0;   
}

bool Kbd_8x5_CH450::toStatus(uint8_t rawdata) {
    return rawdata & 0b01000000;
}

uint8_t Kbd_8x5_CH450::toKeycode(uint8_t rawdata) {

    uint8_t row = (rawdata & 0b00111000) >> 3;  // SEG
    uint8_t col = (rawdata & 0b00000111) - 2;   // DIG

    if (row <= 8 && col <= 5) {
        return keycodeMap[row][col];
    } else {
        return 0;
    }

}
