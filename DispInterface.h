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
        static void display_callback(nut_reg_t *nv);  // specify a register to modify a DispInterface
                                                      // object at recorded address. weird. consider
                                                      // to pass in an address directly.
};

#endif
