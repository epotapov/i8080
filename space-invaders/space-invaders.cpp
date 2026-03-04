#include <cstdint>
#include <iostream>

#include "space-invaders.h"

Space::Space() {
    
}

Space::~Space() {
    
}

void Space::inPort(I8080* i8080, uint8_t port) {
    switch (port)
    {
        case 0:
            break; // Never used
        case 1:
            i8080->a = port1;
            break;
        case 2:
            i8080->a = port2;
            break;
        case 3:
            i8080->a = (shiftWord >> (8 - shiftOffset)) & 0xff;
            break;
        default:
            break;
    }
}

void Space::outPort(I8080* i8080, uint8_t port) {
    switch (port)
    {
        case 2:
            shiftOffset = i8080->a & 0x7;
            break;
        case 3: // Sound
            break;
        case 4:
            shiftWord = (i8080->a << 8) | (shiftWord >> 8);
            break;
        case 5: // Sound
            break;
        case 6: // Watchdog
            break;
        default:
            break;
    }
}

int main(int argc, char** argv) {
    std::cout << "Space Invaders\n";
    return 0;
}