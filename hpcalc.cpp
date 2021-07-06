#include "hpcalc.h"

HPCalc::HPCalc(DispInterface *dv)
    :display(dv)
{
    // do nothing
}

void HPCalc::init() {
    nv = nut_new_processor(80, display);

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
    static bool shouldUpdateDisplay = true;
    readKeys();
    executeCycle();
    if (shouldUpdateDisplay) updateDisplay();
    shouldUpdateDisplay = !shouldUpdateDisplay;
}

void HPCalc::updateDisplay() {
    DispInterface::display_callback(nv);
}

void HPCalc::executeCycle() {
    for (int i = 0; i < 500; i++) {
        nut_execute_instruction(nv);
    }
}

void HPCalc::readKeys() {
    static bool delay = false;
    int key;

    if (delay) {
        delay = false;
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
                    delay = true;
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
