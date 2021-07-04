#include "KeyQueue.h"

KeyQueue::KeyQueue(){

}

int KeyQueue::getLastKeycode() {
    if (availableKeys > 0){
        return queue[availableKeys - 1];
    }
    return 0;  // Please, check if there is any keycode left in the queue
               // before calling this, to avoid getting false results!
}

void KeyQueue::removeLastKeycode() {
    if (availableKeys > 0){
        availableKeys--;
    }
}

bool KeyQueue::queueKeycode(int newcode) {
    if (availableKeys == KeyQueueMaxSize) {
        return false;
    }

    if (availableKeys > 0) {
        for (uint8_t i = availableKeys; i > 0; i--) {
            queue[i] = queue[i-1];
        }
    }

    availableKeys++;
    queue[0] = newcode;

    return true;
}

uint8_t KeyQueue::count() {
    return availableKeys;
}
