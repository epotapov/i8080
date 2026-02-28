#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "../I8080.h"

#define MEMORY_SIZE 0x10000

static constexpr uint8_t PORT_STATUS_A = 0x00;
static constexpr uint8_t PORT_DATA_A = 0x01;
static constexpr uint8_t PORT_STATUS_B = 0x10;
static constexpr uint8_t PORT_DATA_B = 0x11;
static constexpr uint8_t PORT_SWITCHES = 0xFF;
static constexpr uint8_t SWITCH_BOOT_VALUE = 0b00100010;

void out_port(I8080 *i8080, uint8_t port) {
    if (port != PORT_DATA_A && port != PORT_DATA_B) {
        return;
    }

    uint8_t ch = i8080->a;

    std::cout << static_cast<char>(ch);
}

void in_port(I8080 *i8080, uint8_t port) {
    if (port == PORT_SWITCHES) {
        i8080->a = SWITCH_BOOT_VALUE;
        return;
    }

    if (port == PORT_STATUS_A || port == PORT_STATUS_B) {
        i8080->a = 0x02;
        return;
    }

    if (port == PORT_DATA_A || port == PORT_DATA_B) {
        int input = std::getchar();

        uint8_t ch = static_cast<uint8_t>(input);
        if (ch == '\n') {
            ch = '\r';
        }
        i8080->a = ch;
        return;
    }

    i8080->a = 0x00;
}

int main(int argc, char** argv) {
    uint16_t startAddress = 0x0000;

    I8080 i8080(MEMORY_SIZE, startAddress, "roms/4kbas40.bin");
    i8080.setPorts(in_port, out_port);
    i8080.pc = startAddress;

    while (!i8080.hlt) {
        i8080.nextInstruction();
    }

    return 0;
}