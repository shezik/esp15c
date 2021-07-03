#ifndef __hpcalc__
#define __hpcalc__

#include "proc_nut.h"
#include "DisplayDriver.h"
#include <LittleFS.h>

//#define NNPR_CLOCK 215000.0
//#define NNPR_WSIZE 56.0

class HPCalc {
    protected:
        DisplayContent _display;
        nut_reg_t nv;
        int keyQueue[32];  // !! 32 is probably enough. I don't feel like dealing with dynamic allocation and stuff.
    public:
        void init(DisplayDriver* dv);
        void saveState();
        bool loadState();
        void processKeypress(int code);
        bool keyBufferIsEmpty();
        void tick();
        void updateDisplay();
        char* getDisplayString();
        void readKeys();
};

#endif