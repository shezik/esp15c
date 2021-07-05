#ifndef __hpcalc__
#define __hpcalc__

#include "proc_nut.h"
#include "DispInterface.h"
#include "KeyQueue.h"
#include <FS.h>
#include <LITTLEFS.h>

//#define NNPR_CLOCK 215000.0
//#define NNPR_WSIZE 56.0

class HPCalc {
    private:
        DispInterface *_display;
        nut_reg_t *nv;
        KeyQueue keyQueue;  // !! 32 is probably enough. I don't feel like dealing with dynamic allocation.
    public:
        HPCalc();
        void init(DispInterface *dv);
        void saveState();
        bool loadState();
        void processKeypress(int code);
        bool keyBufferIsEmpty();
        void tick();
        void updateDisplay();
        void executeCycle();
        char* getDisplayString();
        void readKeys();
};

#endif