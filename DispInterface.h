#ifndef __DispInterface__
#define __DispInterface__


// custom display settings
#define numFont u8g2_font_t0_15_mr
#define numFontWidth 8
#define numFontX 2
#define numFontY 30

#define annunciatorFont u8g2_font_6x10_tr
#define annunciatorFontWidth 6
#define annunciatorFontX 2
#define annunciatorFontY 45

  // optimized for 128x64 LCDs and CustomXBMFont. It'd be great if you have a 192x64 or wider display.
#define XBMX 0          // coord X of first character
#define XBMY 23         // coord Y of first character
#define numSpacing 2    // spacing between numbers, better >= point_width + commaOffset, if possible.
#define commaOffset -1  // better be 0 or 1, depending on the font being used or screen size.
#define annSpacing 2    // spacing between annunciators (including minus sign), better >= 2
#define annDistance 2   // distance between top of annunciator and bottom of number
#define arrayOffset 1   // display_segments[i + arrayOffset], self-explanatory. product of insufficient space.


#include <Arduino.h>
#include <U8g2lib.h>
#include "proc_nut.h"  // nut_reg_t defined inside
#include "CustomXBMFont.h"

class DispInterface {
    private:
        U8G2& u8g2;
    public:
        bool lowBat = false;
        DispInterface(U8G2& u8g2_);
        void displayString(const char rawstr_[]);  // usually called by display_callback(nut_reg_t *nv)
        char* parseDisplaySegments(segment_bitmap_t display_segments[]);
        void drawSegments(segment_bitmap_t display_segments[]);
        static void display_callback(nut_reg_t *nv);  // specify a register to modify a DispInterface
                                                      // object at recorded address. weird. consider
                                                      // to pass in an address directly.
};

#endif
