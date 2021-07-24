#include "Kbd_8x5_CH450.h"

Kbd_8x5_CH450::Kbd_8x5_CH450(uint8_t sda_, uint8_t scl_, unsigned int freq_)
    : sda(sda_)
    , scl(scl_)
    , freq(freq_)
{
    // do nothing
}

void Kbd_8x5_CH450::startComm() {
    digitalWrite(sda, HIGH);
    //delay(10);
    digitalWrite(scl, HIGH);
    //delay(10);
    digitalWrite(sda, LOW);
    delay(0.1);
    digitalWrite(scl, LOW);
    //delay(10);
}

void Kbd_8x5_CH450::stopComm() {
    //digitalWrite(scl, LOW);  // if scl is set to low after each operation
    //delay(10);               // we won't need this part
    digitalWrite(sda, LOW);
    //delay(10);
    digitalWrite(scl, HIGH);  // stays high during inactive?
    //delay(10);
    digitalWrite(sda, HIGH);
    //delay(10);
}

bool Kbd_8x5_CH450::writeByte(uint8_t data) {
    for (int8_t i = 7; i > -1; i--) {
        if (data & (1 << i)) {
            digitalWrite(sda, HIGH);
        } else {
            digitalWrite(sda, LOW);
        }
        //delay(10);
        digitalWrite(scl, HIGH);
        delay(0.1);
        digitalWrite(scl, LOW);
        delay(0.1);
    }
    pinMode(sda, INPUT);
    digitalWrite(scl, HIGH);
    delay(0.1);
    bool result = digitalRead(sda);
    //delay(10);
    digitalWrite(scl, LOW);
    pinMode(sda, OUTPUT);  // terminal state: sda = low, scl = low
    //Serial.printf("writeByte result is %d\n", result); //debug
    delay(0.1);  // !!
    return result;
}

uint8_t Kbd_8x5_CH450::readByte() {
    uint8_t data = 0;
    pinMode(sda, INPUT);
    for (int8_t i = 7; i > -1; i--) {
        digitalWrite(scl, HIGH);
        delay(0.1);
        if (digitalRead(sda)) {
            //Serial.println("We've got something"); //debug
            data |= (1 << i);
        }
        digitalWrite(scl, LOW);
        delay(0.1);
    }
    pinMode(sda, OUTPUT);
    digitalWrite(sda, HIGH);
    //delay(10);
    digitalWrite(scl, HIGH);
    delay(0.1);
    digitalWrite(scl, LOW);
    //delay(10);
    return data;
}

bool Kbd_8x5_CH450::init() {

    pinMode(sda, OUTPUT);  // Always change pinMode back to OUTPUT state after fiddling 
    pinMode(scl, OUTPUT);  // with it (changing its mode). We assume it is at OUTPUT state by default.
    
    startComm();
    bool resultA = writeByte(0b01001000);  // magic byte to change settings
    bool resultB = writeByte(0b00000010);  // 0: disable sleep; 00: full intensity (useless here);
                                           // 000: separator; 1: enable keyboard scanner; 0: disable LED segments driver
    stopComm();
    
    return resultA && resultB;

}

uint8_t Kbd_8x5_CH450::getKeyData() {
    startComm();
    bool resultA = writeByte(0b01001111);  // magic byte to request key data
    uint8_t resultB = readByte();
    stopComm();
    //delay(100);
    return resultA ? resultB : 0;   
}

bool Kbd_8x5_CH450::toState(uint8_t rawdata) {
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
