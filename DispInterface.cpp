#include "DispInterface.h"

DispInterface::DispInterface(U8G2& u8g2_)
    : u8g2(u8g2_)
{
    // do nothing
}

// rawstr_[48] should be a valid string, I'm not gonna wipe that ass for you.
void DispInterface::displayString(const char rawstr_[]) { 

    uint8_t i;
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

        for (uint8_t j = 1; j < (9 + 1); j++) {  //  here comes danger of memory access violation since we intentionally skipped a '\0' (solved?)
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
    uint8_t j = 0;

    for (uint8_t i = 0; i < MAX_DIGIT_POSITION; i++) {
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

    disp[j++] = '_';  // annunciator separator

    if (lowBat) {disp[j++] = 'L';}  // * (Low Battery Annunciator)

    for (uint8_t i = 0; i < MAX_DIGIT_POSITION; i++) {
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

void DispInterface::drawSegments(segment_bitmap_t display_segments[]) {

    uint8_t xOffset;

    u8g2.clearBuffer();


    // handle digit 0 separately
    if (display_segments[0] & (1 << 6)) {
        u8g2.drawXBM(XBMX, XBMY - minus_height - annDistance, minus_width, minus_height, minus_bits);
    }

    if (lowBat) {
        u8g2.drawXBM(XBMX, XBMY + seg_height + annDistance, asterisk_width, asterisk_height, asterisk_bits);
    }


    for (uint8_t i = 0; i < MAX_DIGIT_POSITION - arrayOffset; i++) {

        if (/*i != 0 && */!display_segments[i + arrayOffset]) continue;

        xOffset = numSpacing * i;

        for (uint8_t ptr = 0; ptr < 9; ptr++) {
            if (display_segments[i + arrayOffset] & (1 << ptr)) {
                switch (ptr) {
                    case 0: u8g2.drawXBM(XBMX + xOffset + seg_width * i, XBMY, seg_width, seg_height, seg_A_bits); break;
                    case 1: u8g2.drawXBM(XBMX + xOffset + seg_width * i, XBMY, seg_width, seg_height, seg_B_bits); break;
                    case 2: u8g2.drawXBM(XBMX + xOffset + seg_width * i, XBMY, seg_width, seg_height, seg_C_bits); break;
                    case 3: u8g2.drawXBM(XBMX + xOffset + seg_width * i, XBMY, seg_width, seg_height, seg_D_bits); break;
                    case 4: u8g2.drawXBM(XBMX + xOffset + seg_width * i, XBMY, seg_width, seg_height, seg_E_bits); break;
                    case 5: u8g2.drawXBM(XBMX + xOffset + seg_width * i, XBMY, seg_width, seg_height, seg_F_bits); break;
                    case 6: u8g2.drawXBM(XBMX + xOffset + seg_width * i, XBMY, seg_width, seg_height, seg_G_bits); break;
                    case 7: u8g2.drawXBM(XBMX + xOffset + seg_width * (i + 1) - comma_width + point_width + commaOffset, XBMY + seg_height - point_height, comma_width, comma_height, seg_H_bits); break;
                    case 8: u8g2.drawXBM(XBMX + xOffset + seg_width * (i + 1) - comma_width + point_width + commaOffset, XBMY + seg_height - point_height, comma_width, comma_height, seg_I_bits); break;
                    // call this CSS, I don't mind.
                }
            }
        }

        if (display_segments[i] & ~511) {
            switch (i) {
                case  2: u8g2.drawXBM(XBMX + asterisk_width                                                                                              + 1 * annSpacing, XBMY + seg_height + annDistance, USER_width,  USER_height,  USER_bits);  break;
                case  3: u8g2.drawXBM(XBMX + asterisk_width + USER_width                                                                                 + 2 * annSpacing, XBMY + seg_height + annDistance, f_width,     f_height,     f_bits);     break;
                case  4: u8g2.drawXBM(XBMX + asterisk_width + USER_width + f_width                                                                       + 3 * annSpacing, XBMY + seg_height + annDistance, g_width,     g_height,     g_bits);     break;
                case  5: u8g2.drawXBM(XBMX + asterisk_width + USER_width + f_width + g_width                                                             + 4 * annSpacing, XBMY + seg_height + annDistance, BEGIN_width, BEGIN_height, BEGIN_bits); break;
                case  6: u8g2.drawXBM(XBMX + asterisk_width + USER_width + f_width + g_width + BEGIN_width                                               + 5 * annSpacing, XBMY + seg_height + annDistance, G__width,    G__height,    G__bits);    break;
                case  7: u8g2.drawXBM(XBMX + asterisk_width + USER_width + f_width + g_width + BEGIN_width + G__width                                    + 5 * annSpacing, XBMY + seg_height + annDistance, _RAD_width,  _RAD_height,  _RAD_bits);  break;
                case  8: u8g2.drawXBM(XBMX + asterisk_width + USER_width + f_width + g_width + BEGIN_width + G__width + _RAD_width                       + 6 * annSpacing, XBMY + seg_height + annDistance, DMY_width,   DMY_height,   DMY_bits);   break;
                case  9: u8g2.drawXBM(XBMX + asterisk_width + USER_width + f_width + g_width + BEGIN_width + G__width + _RAD_width + DMY_width           + 7 * annSpacing, XBMY + seg_height + annDistance, C_width,     C_height,     C_bits);     break;
                case 10: u8g2.drawXBM(XBMX + asterisk_width + USER_width + f_width + g_width + BEGIN_width + G__width + _RAD_width + DMY_width + C_width + 8 * annSpacing, XBMY + seg_height + annDistance, PRGM_width,  PRGM_height,  PRGM_bits);  break;
            }
        }

        /*
        if (lowBat && i == 0) {
            u8g2.drawXBM(XBMX, XBMY + seg_height + annDistance, asterisk_width, asterisk_height, asterisk_bits);
        }
        */

    }

    u8g2.sendBuffer();

}

void DispInterface::display_callback(nut_reg_t *nv) {

    static segment_bitmap_t last_segments[MAX_DIGIT_POSITION] = {'\0'};
    static bool last_lowBat = false;
    bool shouldUpdate = false;

    if (last_lowBat != (*(DispInterface *)(nv->display)).lowBat) {

        last_lowBat = (*(DispInterface *)(nv->display)).lowBat;
        shouldUpdate = true;
        
    } else {

        for (uint8_t i = 0; i < MAX_DIGIT_POSITION; i++) {

            if (shouldUpdate == false && (nv->display_segments[i] != last_segments[i])) {
                shouldUpdate = true;
            }

            if (shouldUpdate == true) {  // starts from where is different
                last_segments[i] = nv->display_segments[i];
            }
        }

    }

    if (!shouldUpdate) return;

#ifdef USE_DISPLAY_STRING
    char *dispString = (*(DispInterface *)(nv->display)).parseDisplaySegments(nv->display_segments);
    Serial.println(dispString);

    /*
    for (uint8_t i = 0; i < MAX_DIGIT_POSITION; i++) {  // debug
        Serial.printf("%X ", nv->display_segments[i]);
    }
    Serial.printf("\n");
    */

    (*(DispInterface *)(nv->display)).displayString(dispString);
#else
    (*(DispInterface *)(nv->display)).drawSegments(nv->display_segments);
#endif

}
