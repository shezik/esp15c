# Todo list:
- ~~implement DispInterface (including ui design and intense U8g2)~~ UI looks kinda bad
- ~~util.c~~
- ~~get rid of MCP23016~~
- ch450 driver (keys can be held down)
- ~~multitasking~~ pointless
- implement save & load states
- get rid of dynamic allocations (convert C structures to C++ classes)
- change exit codes
- add some menus
- figure out what keycode -1 actually stands for

~~What about we skip converting register to string in display update process of display_register->string->display, only doing so when requested?~~ this is fast enough.
