#include "DispInterface.h"

DispInterface::DispInterface(U8G2& u8g2_)
    : _u8g2(u8g2_)
{
    // do nothing
}

void DispInterface::init() {
    // intense u8g2 stuff here
}

void DispInterface::displayString(char *str) {

}

void DispInterface::getDisplayString(nut_reg_t *nv) {

    //Serial.printf("Going into %s!\n", __func__); //debug
    segment_bitmap_t display_segments[MAX_DIGIT_POSITION];
    static segment_bitmap_t last_segments[MAX_DIGIT_POSITION];
    bool shouldUpdate = false;

    for (int i = 0; i < MAX_DIGIT_POSITION; i++) {
        display_segments[i] = nv->display_segments[i];
    }
    
    for (int i = 0; i < MAX_DIGIT_POSITION; i++) {
        if (display_segments[i] != last_segments[i]) {
            shouldUpdate = true;
        }
        last_segments[i] = display_segments[i];
    }

    if (!shouldUpdate) return;
    
    char disp[2 * MAX_DIGIT_POSITION + 1];

    for (int j = 0; j < (2 * MAX_DIGIT_POSITION + 1); j++) {
        disp[j] = '\0';
    }

    int j = 0;
    for (int i = 0; i < MAX_DIGIT_POSITION; i++) {
        switch (display_segments[i] & 0b01111111) {
            case 0b01000000: disp[j++] = '-'; break;
            case 0b00111111: disp[j++] = '0'; break;
            case 0b00000110: disp[j++] = '1'; break;
            case 0b01011011: disp[j++] = '2'; break;
            case 0b01001111: disp[j++] = '3'; break;
            case 0b01100110: disp[j++] = '4'; break;
            case 0b01101101: disp[j++] = '5'; break;
            case 0b01111101: disp[j++] = '6'; break;
            case 0b00000111: disp[j++] = '7'; break;
            case 0b01111111: disp[j++] = '8'; break;
            case 0b01101111: disp[j++] = '9'; break;
            case 0b01110011: disp[j++] = 'P'; break;
            case 0b01111001: disp[j++] = 'E'; break;
            case 0b00000010: disp[j++] = 'i'; break;
            case 0b00100011: disp[j++] = 'n'; break;
            case 0b01011100: disp[j++] = 'O'; break;
            case 0b01010000: disp[j++] = 'R'; break;
            case 0b00100001: disp[j++] = 'r'; break;
            case 0b01100010: disp[j++] = 'u'; break;
            case 0b01111100: disp[j++] = 'b'; break;
            case 0b01011110: disp[j++] = 'd'; break;
            case 0b01110100: disp[j++] = 'h'; break;
            case 0b01110111: disp[j++] = 'A'; break;
            case 0b00111001: disp[j++] = 'C'; break;
            case 0b01110001: disp[j++] = 'F'; break;
            case 0b00000000: disp[j++] = ' '; break;
            default: warning("Unknown segment: %d\n", display_segments[i]);
        }

        if (display_segments[i] & 0b000100000000) {
            disp[j++] = ',';
        } else if (display_segments[i] & 0b10000000) {
            disp[j++] = '.';
        }
    }

    Serial.println(disp);
}

void DispInterface::display_callback(nut_reg_t *nv) {
    //Serial.printf("Going into %s!\n", __func__); //debug
    (*(DispInterface *)(nv->display)).getDisplayString(nv);
}

void DispInterface::showFlagLowBat(bool visible) {

}

void DispInterface::showFlagF(bool visible) {

}

void DispInterface::showFlagG(bool visible) {

}

void DispInterface::showFlagC(bool visible) {

}

void DispInterface::showUser(bool visible) {

}

void DispInterface::showBegin(bool visible) {

}

void DispInterface::showDMY(bool visible) {

}

void DispInterface::showPrgm(bool visible) {

}

void DispInterface::showComma(bool visible, int position) {

}

void DispInterface::showDecimal(bool visible, int position) {

}

void DispInterface::showDeg() {

}

void DispInterface::showGrad(bool isRad) {

}
