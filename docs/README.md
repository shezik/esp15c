# esp15c - 🚧 Work in progress! 🚧
 ESP32 port of [Eric Smith's Nonpareil](https://nonpareil.brouhaha.com/) calculator emulator, currently planned to only support HP-15C.  
 Based on [Tom Fors' early iPhone port](https://code.google.com/archive/p/hpcalc-iphone/).

Currently constructing basic structures.

## Why ESP32?
- ESP32 has more RAM than ESP8266, enough for 15C's ROM and dozens of registers
- ESP32 costs no more than 1 dollar compared to ESP8266
- ESP32 has more GPIOs, freeing us from IO expanders

### Can we support ESP8266 later?
I'm too lazy to optimize RAM consumptions or even implement page files. Feel free to do it on your own. :)

## Components
- 1x ESP32
- 1x CH450 keyboard scanner chip
- 1x 12864 LCD or anything that is 1. big enough and 2. supported by U8g2 library.
