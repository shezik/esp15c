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

char* DispInterface::getDisplayString(nut_reg_t *nv) {
    
}

void DispInterface::display_callback(nut_reg_t *nv) {

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

void DispInterface::setDeg() {

}

void DispInterface::setRad() {

}

void DispInterface::setGrad() {

}
