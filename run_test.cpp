#include <iostream>

#include "I8080.h"

#define MEMORY_SIZE 0x10000

int main(int argc, char** argv) {
    I8080 i8080(MEMORY_SIZE, 0x100, "test/TST8080.COM");
    i8080.memory[0x0000] = 0xD3;
    i8080.memory[0x0001] = 0x00;
    i8080.memory[0x0005] = 0xD3;
    i8080.memory[0x0006] = 0x01;
    i8080.memory[0x0007] = 0xC9;
    i8080.pc = 0x100;
    uint32_t total_inst = 0;
    while (!i8080.test_end) {
        total_inst++;
        i8080.nextInstruction();
    }

    std::cout << std::endl << std::endl << "Test results" << std::endl;
    std::cout << "Expected cycles: " << 4924LU << std::endl;
    std::cout << "Ran cycles: " << i8080.cycle << std::endl;
    return 0;
}