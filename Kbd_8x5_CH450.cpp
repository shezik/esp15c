#include "Kbd_8x5_CH450.h"

void Kbd_8x5_CH450::init() {
    Wire.beginTransmission(0x40);   // !! 0??
    Wire.write(0b01001000);      // magic byte to change settings
    Wire.write(0b00000010);      // 0: disable sleep; 00: full intensity (useless here);
                                 // 000: separator; 1: enable keyboard scanner; 0: disable LED segments driver
    Wire.endTransmission(true);  // release bus
}

uint8_t Kbd_8x5_CH450::requestByte() {
    Wire.beginTransmission(0x40);     // !! 0?? (duplicate)
    Wire.write(0b01001111);        // magic byte to request key data
    Wire.endTransmission(false);   // don't send stop msg yet!
    Wire.requestFrom(0, 1, true);  // request a byte, then release bus
    return Wire.read();
}

inline uint8_t Kbd_8x5_CH450::toStatus(uint8_t rawdata) {
    return (rawdata >> 5);
}

uint8_t Kbd_8x5_CH450::toKeycode(uint8_t rawdata) {

}
