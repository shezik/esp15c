#include "hpcalc.h"

HPCalc::HPCalc(){

}

void HPCalc::init(DisplayDriver* dv) {

    _display = dv;
    nv = nut_new_processor(80, NULL);
    File objFile = LittleFS.open("/15c.obj", "r");

    if(!this.loadState()) {
        this.processKeypress(24);  // auto on
        this.processKeypress(-1);
        this.processKeypress(129);  // backspace key, clears Pr Error
        this.processKeypress(-1);
    } else {
        this.processKeypress(24);  // auto on
        this.processKeypress(-1);
        this.processKeypress(24);  // auto on again
        this.processKeypress(-1);
        // !! why do we need to toggle power state twice?
    }

}

void saveState(){

}

bool loadState(){

}

void processKeypress(int code){

}

bool keyBufferIsEmpty(){

}

void tick(){

}

void updateDisplay(){

}

char* getDisplayString(){

}

void readKeys(){

}

/*

void shutdown() is for saving state when closing the app
which is unnecessary in embedded systems.
But it could be useful if we use a button to turn ESP8266 on/off
instead of merely cutting power with a switch.
Another time.

Parsing input as string is not supported, therefore
void playMacro() and related functions will not be implemented.

*/
