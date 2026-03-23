#include <cstdint>
#include <SDL2/SDL.h>

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

    // SDL stuff
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    uint8_t SDL_init();
    void SDL_loop();
    void SDL_close();
    bool processInput(SDL_Event* event);
};

#endif
