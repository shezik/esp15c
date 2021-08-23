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
        //processKeypress(129);  // backspace key, clears Pr Error
        //processKeypress(-1);
    } else {
        processKeypress(24);  // auto on
        processKeypress(-1);
        processKeypress(24);  // auto on again
        processKeypress(-1);
        // !! why do we need to toggle power state twice?
    }

}

void HPCalc::saveState() {
    File saveFile = SPIFFS.open("/save.bin", "w+");

    saveFile.close();
}

bool HPCalc::loadState() {
    /* debug
    File saveFile = SPIFFS.open("/save.bin", "r");
    
    if(!saveFile){
        Serial.println("No save file!"); //debug
        return false;
    };
    
    saveFile.close();
    return true;
    */
   return false;
}

void HPCalc::processKeypress(int code) {
    keyQueue.queueKeycode(code);
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

void HPCalc::executeCycle(unsigned int count) {
    for (unsigned int i = 0; i < count; i++) {
        nut_execute_instruction(nv);
    }
}

/*
void HPCalc::readKeys() {
    static bool delay = false;
    int key;

    if (delay) {
        delay = false;
    } else {
        if (keyQueue.count()) {
            key = keyQueue.getLastKeycode();
            //Serial.printf("Stage 1: Keycode: %d\n", key); //debug
            keyQueue.removeLastKeycode();
            if (key >= 0) {
                nut_press_key(nv, key);
            } else {
                nut_release_key(nv);
            }

            if (key == -1) {  // !! why?
                if (keyQueue.count()) {
                    key = keyQueue.getLastKeycode();
                    //Serial.printf("Stage 2: Keycode: %d\n", key); //debug
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
*/

/*

    normally we take one key from queue, if key >=0 then press the key, otherwise release any key pressed;

    but if key == -1, it means that we first release all keys pressed, take a key, press it, or release any key pressed (which is pointless),
    then skip next key handler call, delaying the process of next key by 500 nut cycles.

    why do we need it? maybe it is used for simulating long-pressing a key. so I have decided that it is no longer necessary.
    it could be remains of macros and nonsense from the iOS port.

*/

// here comes the new lite version.
void HPCalc::readKeys() {
    if (keyQueue.count()) {
        int key = keyQueue.getLastKeycode();
        keyQueue.removeLastKeycode();

        if (key >= 0) {
            nut_press_key(nv, key);
        } else {
            nut_release_key(nv);
        }
    }
}
