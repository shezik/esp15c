#ifndef __KeyQueue__
#define __KeyQueue__

#define KeyQueueMaxSize 32

#include <Arduino.h>  // for uint8_t definition

class KeyQueue
{
    private:
        int queue[KeyQueueMaxSize];
        uint8_t availableKeys = 0;
    public:
        KeyQueue();
        int getLastKeycode();
        void removeLastKeycode();
        bool queueKeycode(int newcode);
        uint8_t count();
};

#endif
