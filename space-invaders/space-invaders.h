#include <cstdint>

#include "../I8080.h"

#ifndef SPACE_INVADERS
#define SPACE_INVADERS

#define DISPLAY_WIDTH 224
#define DISPLAY_HEIGHT 256

#define INVADERS_H_ADDR 0x0000
#define INVADERS_G_ADDR 0x0800
#define INVADERS_F_ADDR 0x1000
#define INVADERS_E_ADDR 0x1800

#define MEMORY_SIZE 0x4000

struct Space {
    Space();
    ~Space();

    void inPort(I8080* i8080, uint8_t port);
    void outPort(I8080* i8080, uint8_t port);

    uint16_t shiftWord = 0;
    uint8_t shiftOffset = 0;
    uint8_t port1 = 0, port2 = 0;
    uint8_t display[DISPLAY_HEIGHT][DISPLAY_WIDTH] = {0};
    I8080* i8080 = nullptr;
};

#endif
