#include <cstdint>
#include <iostream>
#include <raylib.h>

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

void Space::Ray_initAudio() {
    InitAudioDevice();

    if (IsAudioDeviceReady()) {
        audioInitialized = true;
        // Load sounds
        ufoHitSound = LoadSound("audio/0.wav");
        shootSound = LoadSound("audio/1.wav");
        playerDieSound = LoadSound("audio/2.wav");
        alienDieSound = LoadSound("audio/3.wav");
        alienMove1 = LoadSound("audio/4.wav");
        alienMove2 = LoadSound("audio/5.wav");
        alienMove3 = LoadSound("audio/6.wav");
        alienMove4 = LoadSound("audio/7.wav");
        ufoSound = LoadSound("audio/8.wav");
    }
}

void Space::Ray_playAudio(bool bank) {
    if (!audioInitialized) return;

    uint8_t data = i8080->a;

    if (bank) {
        if (data != lastPort3) {
            if ((data & 0x1) && !(lastPort3 & 0x1)) {
                PlaySound(ufoHitSound);
            }
            if ((data & 0x2) && !(lastPort3 & 0x2)) {
                PlaySound(shootSound);
            }
            if ((data & 0x4) && !(lastPort3 & 0x4)) {
                PlaySound(playerDieSound);
            }
            if ((data & 0x8) && !(lastPort3 & 0x8)) {
                PlaySound(alienDieSound);
            }
            lastPort3 = data;
        }
    }
    else {
        if (data != lastPort5) {
            if ((data & 0x1) && !(lastPort5 & 0x1)) {
                PlaySound(alienMove1);
            }
            if ((data & 0x2) && !(lastPort5 & 0x2)) {
                PlaySound(alienMove2);
            }
            if ((data & 0x4) && !(lastPort5 & 0x4)) {
                PlaySound(alienMove3);
            }
            if ((data & 0x8) && !(lastPort5 & 0x8)) {
                PlaySound(alienMove4);
            }
            if ((data & 0x10) && !(lastPort5 & 0x10)) {
                PlaySound(ufoSound);
            }
            lastPort5 = data;
        }
    }
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
            Ray_playAudio(true);
            break;
        case 4:
            shiftWord = (i8080->a << 8) | (shiftWord >> 8);
            break;
        case 5: // Sound
            Ray_playAudio(false);
            break;
        case 6: // Watchdog
            break;
        default:
            break;
    }
}

void Space::Ray_init() {
    InitWindow(DISPLAY_WIDTH * SCALE, DISPLAY_HEIGHT * SCALE, "Space Invaders");
    SetTargetFPS(60);

    Image img = GenImageColor(DISPLAY_WIDTH, DISPLAY_HEIGHT, BLACK);
    texture = LoadTextureFromImage(img);
    UnloadImage(img);
}

void Space::Ray_loop() {
    bool running = true;
    uint32_t dt = 0;

    while (!WindowShouldClose() && running) {
        float dtf = GetFrameTime();
        dt = (uint32_t)(dtf * 1000.0f);

        running = processInput();

        // Render
        runGame(dt);

        BeginDrawing();
            ClearBackground(BLACK);
            DrawTextureEx(texture, (Vector2) {0, 0}, 0.0f, (float) SCALE, WHITE);
        EndDrawing();
    }
}

bool Space::processInput() {
    // exit
    if (IsKeyPressed(KEY_ESCAPE)) {
        return false;
    }

    // coin
    if (IsKeyDown(KEY_C)) {
        port1 |= 0x1;
    }
    else {
        port1 &= 0b11111110;
    }

    // Start 1p
    if (IsKeyDown(KEY_S)) {
        port1 |= 1 << 2;
    }
    else {
        port1 &= 0b11111011;
    }

    // Start 2p
    if (IsKeyDown(KEY_DOWN)) {
        port1 |= 1 << 1;
    }
    else {
        port1 &= 0b11111101;
    }

    // Shoot 1p
    if (IsKeyDown(KEY_W)) {
        port1 |= 1 << 4;
    }
    else {
        port1 &= 0b11101111;
    }

    // Shoot 2p
    if (IsKeyDown(KEY_UP)) {
        port2 |= 1 << 4;
    }
    else {
        port2 &= 0b11101111;
    }


    // Left 1p
    if (IsKeyDown(KEY_A)) {
        port1 |= 1 << 5;
    }
    else {
        port1 &= 0b11011111;
    }

    // Left 2p
    if (IsKeyDown(KEY_LEFT)) {
        port2 |= 1 << 5;
    }
    else {
        port2 &= 0b11011111;
    }

    // Right 1p
    if (IsKeyDown(KEY_D)) {
        port1 |= 1 << 6;
    }
    else {
        port1 &= 0b10111111;
    }

    // Right 2p
    if (IsKeyDown(KEY_RIGHT)) {
        port2 |= 1 << 6;
    }
    else {
        port2 &= 0b10111111;
    }

    // Tilt
    if (IsKeyDown(KEY_T)) {
        port2 |= 1 << 2;
    }
    else {
        port2 &= 0b11111011;
    }

    return true;
}

void Space::Ray_close() {
    UnloadTexture(texture);

    // Unload Sounds if audio was initialized
    if (audioInitialized) {
        UnloadSound(ufoSound);
        UnloadSound(shootSound);
        UnloadSound(playerDieSound);
        UnloadSound(alienDieSound);
        UnloadSound(alienMove1);
        UnloadSound(alienMove2);
        UnloadSound(alienMove3);
        UnloadSound(alienMove4);
        UnloadSound(ufoHitSound);

        CloseAudioDevice();
    }
    CloseWindow();
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
            i8080->requestInterrupt(interrupt);

            if (interrupt == 0xd7) {
                drawDisplay();
            }

            if (interrupt == 0xcf) {
                interrupt = 0xd7;
            }
            else {
                interrupt = 0xcf;
            }
        }
    }
}

void Space::drawDisplay() {
    for (uint32_t i = 0; i < (DISPLAY_HEIGHT * DISPLAY_WIDTH) / 8; ++i) {
        const uint32_t y = i * 8 / 256;
        const uint32_t base_x = (i * 8) % 256;

        const uint8_t byte = i8080->memory[VRAM_ADDR + i];

        for (uint8_t bit = 0; bit < 8; ++bit) {
            int px = base_x + bit;
            int py = y;
            const bool pixelOn = (byte >> bit) & 1;

            uint8_t r = 0, g = 0, b = 0;

            if (pixelOn) {
                if (px < 16) {
                    if (py < 16 || py > 118 + 16) {
                        r = 255;
                        g = 255;
                        b = 255;
                    } else {
                        g = 255;
                    }
                } else if (px >= 16 && px <= 16 + 56) {
                    g = 255;
                } else if (px >= 16 + 56 + 120 && px < 16 + 56 + 120 + 32) {
                    r = 255;
                } else {
                    r = 255;
                    g = 255;
                    b = 255;
                }
            }

            uint32_t temp = px;
            px = py;
            py = -temp + DISPLAY_HEIGHT - 1;

            display[py][px][0] = r;
            display[py][px][1] = g;
            display[py][px][2] = b;
            display[py][px][3] = 255;
        }
    }

    UpdateTexture(texture, &display[0][0][0]);
}

int main(int argc, char** argv) {
    Space space;

    space.Ray_init();
    space.Ray_initAudio();

    space.Ray_loop();
    space.Ray_close();
    return 0;
}