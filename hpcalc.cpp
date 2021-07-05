#include "hpcalc.h"

HPCalc::HPCalc() {

}

void HPCalc::init(DispInterface *dv) {

    _display = dv;
    nv = nut_new_processor(80, nullptr);
    nut_read_object_file(nv, "/15c.obj");

    if (!loadState()) {
        processKeypress(24);  // auto on
        processKeypress(-1);
        processKeypress(129);  // backspace key, clears Pr Error
        processKeypress(-1);
    } else {
        processKeypress(24);  // auto on
        processKeypress(-1);
        processKeypress(24);  // auto on again
        processKeypress(-1);
        // !! why do we need to toggle power state twice?
    }

}

void HPCalc::saveState() {
    File saveFile = LittleFS.open("/save.bin", "w+");

    saveFile.close();
}

bool HPCalc::loadState() {
    File saveFile = LittleFS.open("/save.bin", "r");
    
    if(!saveFile){
        return false;
    };
    
    saveFile.close();
    return true;
}

void HPCalc::processKeypress(int code) {
    keyQueue.queueKeycode(code);
}

bool HPCalc::keyBufferIsEmpty() {
    return keyQueue.count() > 0 ? false : true;
}

void HPCalc::tick(){
    static int n = 0;
    readKeys();
    executeCycle();
    if (n++ % 2 == 0) {
        updateDisplay();
        n = 0;
    }
}

void HPCalc::updateDisplay() {

}

void HPCalc::executeCycle() {
    int i = 500;
    while (i-- > 0) {
        nut_execute_instruction(nv);
    }
}

char* HPCalc::getDisplayString() {

}

void HPCalc::readKeys() {
    static int delay = 0;
    int key;

    if (delay) {
        delay--;
    } else {
        if (keyQueue.count()) {
            key = keyQueue.getLastKeycode();
            keyQueue.removeLastKeycode();
            if (key >= 0) {
                nut_press_key(nv, key);
            } else {
                nut_release_key(nv);
            }

            if (key == -1) {
                if (keyQueue.count()) {
                    key = keyQueue.getLastKeycode();
                    keyQueue.removeLastKeycode();
                    if (key >= 0) {
                        nut_press_key(nv, key);
                    } else {
                        nut_release_key(nv);
                    }
                    delay = 1;
                }
            }
        }
    }
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
