#include "DispInterface.h"

DispInterface::DispInterface(U8G2& u8g2_)
    : u8g2(u8g2_)
{
    // do nothing
}

void DispInterface::init() {
    // intense u8g2 stuff here
}

/*
void DispInterface::displayString(char *rawstr) {
    char numbers[48 - 9 - 1];
    char annunciators[9];
    int i;

    for (i = 0; i < (48 - 9 - 1); i++) {
        numbers[i] = rawstr[i];

        if (rawstr[i] = '_') {
            numbers[i] = '\0';
            break;
        }
    }

    numbers[48 - 9 - 1 - 1] = '\0';  // if no underscore was found

    i++;  // skip underscore

    for (int j = 0; j < 9; j++) {
        annunciators[j] = rawstr[i + j];

        if (rawstr[i + j] = '\0') break;
    }

    u8g2.setFont(u8g2_font_freedoomr10_mu);
}
*/

void DispInterface::displayString(char rawstr[]) {

    int i;
    int xOffset = 1;

    u8g2.clearBuffer();
    u8g2.setFontDirection(0);

    u8g2.setFont(u8g2_font_freedoomr10_mu);

    for (i = 0; i < (48 - 9 - 1); i++) {
        if (rawstr[i] == '\0' || rawstr[i] == '_') break;
        switch (rawstr[i]) {
            case '-': u8g2.drawStr(xOffset,30,"-"); xOffset += 9; break;
            case '0': u8g2.drawStr(xOffset,30,"0"); xOffset += 9; break;
            case '1': u8g2.drawStr(xOffset,30,"1"); xOffset += 9; break;
            case '2': u8g2.drawStr(xOffset,30,"2"); xOffset += 9; break;
            case '3': u8g2.drawStr(xOffset,30,"3"); xOffset += 9; break;
            case '4': u8g2.drawStr(xOffset,30,"4"); xOffset += 9; break;
            case '5': u8g2.drawStr(xOffset,30,"5"); xOffset += 9; break;
            case '6': u8g2.drawStr(xOffset,30,"6"); xOffset += 9; break;
            case '7': u8g2.drawStr(xOffset,30,"7"); xOffset += 9; break;
            case '8': u8g2.drawStr(xOffset,30,"8"); xOffset += 9; break;
            case '9': u8g2.drawStr(xOffset,30,"9"); xOffset += 9; break;
            case 'P': u8g2.drawStr(xOffset,30,"P"); xOffset += 9; break;
            case 'E': u8g2.drawStr(xOffset,30,"E"); xOffset += 9; break;
            case 'i': u8g2.drawStr(xOffset,30,"i"); xOffset += 9; break;
            case 'n': u8g2.drawStr(xOffset,30,"n"); xOffset += 9; break;
            case 'O': u8g2.drawStr(xOffset,30,"O"); xOffset += 9; break;
            case 'R': u8g2.drawStr(xOffset,30,"R"); xOffset += 9; break;
            case 'r': u8g2.drawStr(xOffset,30,"r"); xOffset += 9; break;
            case 'u': u8g2.drawStr(xOffset,30,"u"); xOffset += 9; break;
            case 'b': u8g2.drawStr(xOffset,30,"b"); xOffset += 9; break;
            case 'd': u8g2.drawStr(xOffset,30,"d"); xOffset += 9; break;
            case 'h': u8g2.drawStr(xOffset,30,"h"); xOffset += 9; break;
            case 'A': u8g2.drawStr(xOffset,30,"A"); xOffset += 9; break;
            case 'C': u8g2.drawStr(xOffset,30,"C"); xOffset += 9; break;
            case 'F': u8g2.drawStr(xOffset,30,"F"); xOffset += 9; break;
            case ' ': u8g2.drawStr(xOffset,30," "); xOffset += 9; break;
            case ',': u8g2.drawStr(xOffset,30,","); xOffset += 9; break;
            case '.': u8g2.drawStr(xOffset,30,"."); xOffset += 9; break;
            default: warning("Unknown segment: %d\n", rawstr[i]);
        }
    }

    xOffset = 1;
    u8g2.setFont(u8g2_font_6x10_tr);

    for (int j = 1; j < 10; j++) {
        if (rawstr[i + j] == '\0') break;
        switch (rawstr[i + j]) {
            case 'U': u8g2.drawStr(xOffset,45,"USER");  xOffset += 6*4 + 1; break;
            case 'f': u8g2.drawStr(xOffset,45,"f");     xOffset += 6*1 + 1; break;
            case 'g': u8g2.drawStr(xOffset,45,"g");     xOffset += 6*1 + 1; break;
            case 'B': u8g2.drawStr(xOffset,45,"BEGIN"); xOffset += 6*5 + 1; break;
            case 'G': u8g2.drawStr(xOffset,45,"G");     xOffset += 6;       break;
            case 'R': u8g2.drawStr(xOffset,45,"RAD");   xOffset += 6*5 + 1; break;
            case 'D': u8g2.drawStr(xOffset,45,"D.MY");  xOffset += 6*4 + 1; break;
            case 'C': u8g2.drawStr(xOffset,45,"C");     xOffset += 6*1 + 1; break;
            case 'P': u8g2.drawStr(xOffset,45,"PRGM");  xOffset += 6*4 + 1; break;
        }
    }

    u8g2.sendBuffer();
}

char* DispInterface::parseDisplaySegments(segment_bitmap_t display_segments[]) {

    //Serial.printf("Going into %s!\n", __func__); //debug
    static char disp[48];  // must be static

    /*
    for (int j = 0; j < (2 * MAX_DIGIT_POSITION + 1); j++) {
        disp[j] = '\0';
    }
    */

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

    disp[j++] = '_';

    for (int i = 0; i < MAX_DIGIT_POSITION; i++) {
        switch (i) {
            case  2: if (display_segments[i] & ~0b000111111111) {disp[j++] = 'U';} break;  // User
            case  3: if (display_segments[i] & ~0b000111111111) {disp[j++] = 'f';} break;  // f
            case  4: if (display_segments[i] & ~0b000111111111) {disp[j++] = 'g';} break;  // g
            case  5: if (display_segments[i] & ~0b000111111111) {disp[j++] = 'B';} break;  // Begin
            case  6: if (display_segments[i] & ~0b000111111111) {disp[j++] = 'G';} break;  // G(rad)
            case  7: if (display_segments[i] & ~0b000111111111) {disp[j++] = 'R';} break;  // (G)rad
            case  8: if (display_segments[i] & ~0b000111111111) {disp[j++] = 'D';} break;  // D.MY
            case  9: if (display_segments[i] & ~0b000111111111) {disp[j++] = 'C';} break;  // C
            case 10: if (display_segments[i] & ~0b000111111111) {disp[j++] = 'P';} break;  // Prgm
        }
    }

    disp[j++] = '\0';

    return disp;
}

void DispInterface::display_callback(nut_reg_t *nv) {
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

    Serial.println((*(DispInterface *)(nv->display)).parseDisplaySegments(display_segments));
    (*(DispInterface *)(nv->display)).displayString((*(DispInterface *)(nv->display)).parseDisplaySegments(display_segments));
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
