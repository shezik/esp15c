# esp15c - 🚧 Work in progress! 🚧
 ESP32 port of [Eric Smith's Nonpareil](https://nonpareil.brouhaha.com/) calculator emulator, currently planned to only support HP-15C.  
 Based on [Tom Fors' early iPhone port](https://code.google.com/archive/p/hpcalc-iphone/).

## Current status
Emulation seems to be working. Haven't implemented a keyboard yet, it reads from Serial.  
**Any line commented with *debug* is buggy, added to make everything work for now *(bodging)*, or completely unfunctional. Contributions are very welcomed.**

### Installation
Download any library that is missing from Arduino IDE, use [Arduino ESP32 filesystem uploader](https://github.com/me-no-dev/arduino-esp32fs-plugin) to upload 15C ROM into SPIFFS *(no uploader is available for LittleFS so far)*, the check Serial Monitor.

### Request a keypress in Serial
Use this photo to find the keycode you need:  
![a shot of 15C keyboard with keycodes drawn onto it](15c.png)

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
