#include <Arduino.h>
#include "Keyboard_10x4_MCP23016.h"

// Compiler would complain if I didn't move the following code out of class definition
static const uint8_t keyBindings[/*rows=*/4][/*cols=*/10] = {
        { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9},
        {10, 11, 12, 13, 14, 15, 16, 17, 18, 19},
        {20, 21, 22, 23, 24, 25, 26, 27, 28, 29},
        {30, 31, 32, 33, 34, 35, 36, 37, 38, 39} }; // 10x4 keyboard key bindings

Keyboard_10x4_MCP23016::Keyboard_10x4_MCP23016(uint8_t MCPAddress_, uint8_t MCPSDA_, uint8_t MCPSCL_)
    : MCPAddress(MCPAddress_)
    , MCPSDA(MCPSDA_)
    , MCPSCL(MCPSCL_)
{
    // Nothing to place here yet
}

void Keyboard_10x4_MCP23016::init() {
    Wire.begin(/*SDA=*/MCPSDA, /*SCL=*/MCPSCL);
    Wire.setClock(200000); // !!Not sure about this value
    
    // Configure first 4 pins as input and other 12 pins as output
    writeBlockData(IODIR0, 0b00001111);
    writeBlockData(IODIR1, 0b00000000);
}

uint8_t Keyboard_10x4_MCP23016::readBlockData(uint8_t gp) {
    Wire.beginTransmission(MCPAddress);
    Wire.write(gp); 
    Wire.endTransmission();
    delay(10); // Essential delays, comm does not work without them. :(
    Wire.requestFrom(MCPAddress, 1); // Read one byte from chip
    delay(10);
    return Wire.read();
}

void Keyboard_10x4_MCP23016::writeBlockData(uint8_t reg, uint8_t data) {
    Wire.beginTransmission(MCPAddress);
    Wire.write(reg);
    Wire.write(data);
    Wire.endTransmission();
    delay(10);
}

uint8_t Keyboard_10x4_MCP23016::getKey() {

    // 14-pin 10x4 keyboard scanner, one keystroke at a time

    uint8_t coordRow, coordCol = 255;

    writeBlockData(GP0, 0b11110000);
    writeBlockData(GP1, 0b00111111);

    coordRow = (readBlockData(GP0) & 0b00001111);

    writeBlockData(GP0, 0b00000000);
    writeBlockData(GP1, 0b00000000);

    if (coordRow != 1 && coordRow != 2 && coordRow != 4 && coordRow != 8) {
        return 255;
    }

    for (int i = 0; i < 4; i++) {
        writeBlockData(GP0, 0b00010000 << i);
        if (readBlockData(GP0) & 0b00001111) {
            coordCol = i; // coordCol = 0, 1, 2, 3
            break;
        }
    }

    writeBlockData(GP0, 0b00000000);

    coordRow = int(log(coordRow) / log(2)); // coordRow = 0, 1, 2, 3

    if (coordCol != 255) {
        return keyBindings[coordRow][coordCol];
    }

    for (int i = 0; i < 6; i++) {
        writeBlockData(GP1, 0b00000001 << i);
        if (readBlockData(GP0) & 0b00001111) {
            coordCol = i; // coordCol = 0, 1, 2, 3, 4, 5
            break;
        }
    }

    writeBlockData(GP1, 0b00000000);

    if (coordCol == 255) {
        return 255; // Key was released too early
    }

    return keyBindings[coordRow][coordCol + 4];

}