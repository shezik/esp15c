#include "DispInterface.h"

DispInterface::DispInterface(U8G2& u8g2_)
    : u8g2(u8g2_)
{
    // do nothing
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

    u8g2.setFont(numFont);
}
*/

// rawstr_[48] should be a valid string, I'm not gonna wipe that ass for you.
void DispInterface::displayString(const char rawstr_[]) { 

    int i;
    int xOffset = annunciatorFontX;
    bool containsAnnunciators = false;

    char rawstr[48];
    strcpy(rawstr, rawstr_);

    u8g2.clearBuffer();
    u8g2.setFontDirection(0);

    u8g2.setFont(numFont);


    for (i = 0; i < 48; i++) {
        if (rawstr[i] == '\0') {
            break;
        } else if (rawstr[i] == '_') {
            rawstr[i] = '\0';  // two strings one array
            containsAnnunciators = true;
            break;
        }
    }
    
    u8g2.drawStr(numFontX,numFontY,rawstr);

    if (containsAnnunciators) {

        u8g2.setFont(annunciatorFont);

        for (int j = 1; j < (9 + 1); j++) {  //  here comes danger of memory access violation since we intentionally skipped a '\0' (solved?)
            if (rawstr[i + j] == '\0') break;
            switch (rawstr[i + j]) {
                case 'L': u8g2.drawStr(xOffset,annunciatorFontY,"*");     xOffset += annunciatorFontWidth*1 + 2; break;
                case 'U': u8g2.drawStr(xOffset,annunciatorFontY,"USER");  xOffset += annunciatorFontWidth*4 + 2; break;
                case 'f': u8g2.drawStr(xOffset,annunciatorFontY,"f");     xOffset += annunciatorFontWidth*1 + 2; break;
                case 'g': u8g2.drawStr(xOffset,annunciatorFontY,"g");     xOffset += annunciatorFontWidth*1 + 2; break;
                case 'B': u8g2.drawStr(xOffset,annunciatorFontY,"BEGIN"); xOffset += annunciatorFontWidth*5 + 2; break;
                case 'G': u8g2.drawStr(xOffset,annunciatorFontY,"G");     xOffset += annunciatorFontWidth*1 + 0; break;
                case 'R': u8g2.drawStr(xOffset,annunciatorFontY,"RAD");   xOffset += annunciatorFontWidth*5 + 2; break;
                case 'D': u8g2.drawStr(xOffset,annunciatorFontY,"D.MY");  xOffset += annunciatorFontWidth*4 + 2; break;
                case 'C': u8g2.drawStr(xOffset,annunciatorFontY,"C");     xOffset += annunciatorFontWidth*1 + 2; break;
                case 'P': u8g2.drawStr(xOffset,annunciatorFontY,"PRGM");  xOffset += annunciatorFontWidth*4 + 2; break;
                default: warning("Unknown segment: %d\n", rawstr[i + j]);
            }
        }
    }

    u8g2.sendBuffer();

}

char* DispInterface::parseDisplaySegments(segment_bitmap_t display_segments[]) {

    static char disp[48];  // must be static; !! estimated value!
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

    if (lowBat) {disp[j++] = 'L';}  // * (Low Battery Annunciator)

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
    static segment_bitmap_t last_segments[MAX_DIGIT_POSITION] = {'\0'};
    bool shouldUpdate = false;

    for (int i = 0; i < MAX_DIGIT_POSITION; i++) {
        display_segments[i] = nv->display_segments[i];

        if (display_segments[i] != last_segments[i]) {
            shouldUpdate = true;
        }
        last_segments[i] = display_segments[i];
    }

    if (!shouldUpdate) return;


    Serial.println((*(DispInterface *)(nv->display)).parseDisplaySegments(display_segments));
    (*(DispInterface *)(nv->display)).displayString((*(DispInterface *)(nv->display)).parseDisplaySegments(display_segments));

}
