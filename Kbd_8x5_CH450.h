#ifndef __Kbd_8x5_CH450__
#define __Kbd_8x5_CH450__

#include <Arduino.h>
#include <Wire.h>

class Kbd_8x5_CH450 {
    public:
        bool keyIsDown = false;
        void init();
        uint8_t requestByte();
        inline uint8_t toStatus(uint8_t rawdata);
        uint8_t toKeycode(uint8_t rawdata);
};

#endif
