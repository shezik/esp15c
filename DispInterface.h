#ifndef __DispInterface__
#define __DispInterface__

#include <Arduino.h>
#include <U8g2lib.h>
#include "proc_nut.h"  // nut_reg_t defined inside

class DispInterface {
    private:
        U8G2& _u8g2;
        void showFlagLowBat(bool visible);
        void showFlagF(bool visible);
        void showFlagG(bool visible);
        void showFlagC(bool visible);
        void showUser(bool visible);
        void showBegin(bool visible);
        void showDMY(bool visible);
        void showPrgm(bool visible);
        void showComma(bool visible, int position);
        void showDecimal(bool visible, int position);
        void showDeg();
        void showGrad(bool isRad);
    public:
        DispInterface(U8G2& u8g2_);
        void init();
        void displayString(char *str);  // usually called by display_callback(nut_reg_t *nv)
        void getDisplayString(nut_reg_t *nv);
        static void display_callback(nut_reg_t *nv);  // specify a register to modify a DispInterface
                                                      // object at recorded address. weird. consider
                                                      // to pass in an address directly.
};

#endif