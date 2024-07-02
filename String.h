#ifndef STRING_H
#define STRING_H
#include "Hook.h"
class String
{
    char gap380138[20];
public:
    String(char* contents) {
        ((void (*)(String*, char*))(base + 0xA078F8))(this, contents);
    }
    ~String() {
        ((void (*)(String*))(base + 0x999D90))(this);
    }
};
#endif