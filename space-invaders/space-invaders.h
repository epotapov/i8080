#include <cstdint>
#include <raylib.h>

#include "../I8080.h"

#ifndef SPACE_INVADERS
#define SPACE_INVADERS

#define DISPLAY_WIDTH 224
#define DISPLAY_HEIGHT 256
#define SCALE 3

#define INVADERS_H_ADDR 0x0000
#define INVADERS_G_ADDR 0x0800
#define INVADERS_F_ADDR 0x1000
#define INVADERS_E_ADDR 0x1800

#define MEMORY_SIZE 0x4000
#define FPS 59.541985
#define CLOCK_SPEED 1996800
#define CYCLES_PER_FRAME (CLOCK_SPEED / FPS)

#define VRAM_ADDR 0x2400

struct Space {
    Space();
    ~Space();

    void inPort(I8080* i8080, uint8_t port);
    void outPort(I8080* i8080, uint8_t port);

    void drawDisplay();
    void runGame(uint32_t ms);

    uint16_t shiftWord = 0;
    uint8_t shiftOffset = 0;
    uint8_t port1 = 0, port2 = 0;
    uint8_t display[DISPLAY_HEIGHT][DISPLAY_WIDTH][4] = {0};
    I8080* i8080 = nullptr;
    uint8_t interrupt = 0xcf;

    uint8_t lastPort3 = 0;
    uint8_t lastPort5 = 0;

    // raylib stuff
    Texture2D texture;
    Sound ufoHitSound;
    Sound shootSound;
    Sound playerDieSound;
    Sound alienDieSound;
    Sound alienMove1;
    Sound alienMove2;
    Sound alienMove3;
    Sound alienMove4;
    Sound ufoSound;
    bool audioInitialized = false;
    void Ray_init();
    void Ray_loop();
    void Ray_close();
    void Ray_initAudio();
    void Ray_playAudio(bool bank);
    bool processInput();
};

#endif
