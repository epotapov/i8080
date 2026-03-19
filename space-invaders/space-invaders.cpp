#include <cstdint>
#include <iostream>
#include <SDL2/SDL.h>

#include "space-invaders.h"

Space::Space() {
    i8080 = new I8080(MEMORY_SIZE, INVADERS_H_ADDR, "roms/invaders.h");
    i8080->writeRom(INVADERS_G_ADDR, "roms/invaders.g");
    i8080->writeRom(INVADERS_F_ADDR, "roms/invaders.f");
    i8080->writeRom(INVADERS_E_ADDR, "roms/invaders.e");
    i8080->setPorts(
        [this] (I8080* cpu, uint8_t port) { inPort(cpu, port); },
        [this] (I8080* cpu, uint8_t port) { outPort(cpu, port); }
    );
}

Space::~Space() {
    delete i8080;
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

uint8_t Space::SDL_init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << "\n";
        return 1;
    }

    window = SDL_CreateWindow(
        "Space Invaders",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        DISPLAY_WIDTH * SCALE, DISPLAY_HEIGHT * SCALE,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(
        window, 1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!renderer) {
        std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    texture = SDL_CreateTexture(
        renderer, SDL_PIXELFORMAT_RGBA32,
        SDL_TEXTUREACCESS_STREAMING, DISPLAY_WIDTH, DISPLAY_HEIGHT
    );

    if (!renderer) {
        std::cerr << "SDL_CreateTexture failed: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    return 0;
}

void Space::SDL_loop() {
    SDL_Event event;
    bool running = true;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else {
                running = processInput(&event);
            }
        }

        // Render


    }
}

bool Space::processInput(SDL_Event* event) {
    switch (event->type) {
        case SDL_KEYDOWN: {
            switch (event->key.keysym.sym) {
                case SDLK_ESCAPE:
                    return false;
                case SDLK_c:
                    // coin
                    port1 |= 0x1;
                    break;
                case SDLK_s:
                    // Start 1p
                    port1 |= 1 << 2;
                    break;
                case SDLK_DOWN:
                    // Start 2p
                    port1 |= 1 << 1;
                    break;
                case SDLK_w:
                    // Shoot 1p
                    port1 |= 1 << 4;
                    break;
                case SDLK_UP:
                    // Shoot 2p
                    port2 |= 1 << 4;
                    break;
                case SDLK_a:
                    // Left 1p
                    port1 |= 1 << 5;
                    break;
                case SDLK_LEFT:
                    // Left 2p
                    port2 |= 1 << 5;
                    break;
                case SDLK_d:
                    // Right 1p
                    port1 |= 1 << 6;
                    break;
                case SDLK_RIGHT:
                    // Right 2p
                    port2 |= 1 << 6;
                    break;
                case SDLK_t:
                    // Tilt
                    port2 |= 1 << 2;
                    break;
                default:
                    break;
            }
        } break;
        case SDL_KEYUP: {
            switch (event->key.keysym.sym) {
                case SDLK_ESCAPE:
                    return false;
                case SDLK_c:
                    // coin
                    port1 &= 0b11111110;
                    break;
                case SDLK_s:
                    // Start 1p
                    port1 &= 0b11111011;
                    break;
                case SDLK_DOWN:
                    // Start 2p
                    port1 &= 0b11111101;
                    break;
                case SDLK_w:
                    // Shoot 1p
                    port1 &= 0b11101111;
                    break;
                case SDLK_UP:
                    // Shoot 2p
                    port2 &= 0b11101111;
                    break;
                case SDLK_a:
                    // Left 1p
                    port1 &= 0b11011111;
                    break;
                case SDLK_LEFT:
                    // Left 2p
                    port2 &= 0b11011111;
                    break;
                case SDLK_d:
                    // Right 1p
                    port1 &= 0b10111111;
                    break;
                case SDLK_RIGHT:
                    // Right 2p
                    port2 &= 0b10111111;
                    break;
                case SDLK_t:
                    // Tilt
                    port2 &= 0b11111011;
                    break;
                default:
                    break;
            }
        } break;
    }
    return true;
}

void Space::SDL_close() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Space::runGame(uint32_t ms) {
    int numCycles = 0;

    while (numCycles < ms * CLOCK_SPEED / 1000) {
        uint64_t origCycle = i8080->cycle;

        i8080->nextInstruction();
        uint64_t changeCycle = i8080->cycle - origCycle;
        numCycles += changeCycle;

        if (i8080->cycle >= CYCLES_PER_FRAME / 2) {
            i8080->cycle -= CYCLES_PER_FRAME / 2;
        }
    }
}

void Space::drawDisplay() {
    
}

int main(int argc, char** argv) {
    Space space;

    uint8_t fail = space.SDL_init();

    if (fail) {
        return 1;
    }

    space.SDL_loop();
    space.SDL_close();
    return 0;
}