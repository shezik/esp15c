#ifndef HEADER_KBD_10X4_MCP23016
#define HEADER_KBD_10X4_MCP23016

#include <Wire.h>
#include <math.h>

class Keyboard_10x4_MCP23016
{
    private:
        static const uint8_t GP0     = 0x00;  // DATA PORT REGISTER 0
        static const uint8_t GP1     = 0x01;  // DATA PORT REGISTER 1
        static const uint8_t OLAT0   = 0x02;  // OUTPUT LATCH REGISTER 0
        static const uint8_t OLAT1   = 0x03;  // OUTPUT LATCH REGISTER 1
        static const uint8_t IPOL0   = 0x04;  // INPUT POLARITY PORT REGISTER 0
        static const uint8_t IPOL1   = 0x05;  // INPUT POLARITY PORT REGISTER 1
        static const uint8_t IODIR0  = 0x06;  // I/O DIRECTION REGISTER 0
        static const uint8_t IODIR1  = 0x07;  // I/O DIRECTION REGISTER 1
        static const uint8_t INTCAP0 = 0x08;  // INTERRUPT CAPTURE REGISTER 0
        static const uint8_t INTCAP1 = 0x09;  // INTERRUPT CAPTURE REGISTER 1
        static const uint8_t IOCON0  = 0x0A;  // I/O EXPANDER CONTROL REGISTER 0
        static const uint8_t IOCON1  = 0x0B;  // I/O EXPANDER CONTROL REGISTER 1

        uint8_t MCPAddress, MCPSDA, MCPSCL;
        uint8_t readBlockData(uint8_t gp);
        void writeBlockData(uint8_t reg, uint8_t data);

    public:
        Keyboard_10x4_MCP23016(uint8_t MCPAddress_ = 0x20, uint8_t MCPSDA_ = D2, uint8_t MCPSCL_ = D1);
        uint8_t getKey();
        void init();
};

#endif