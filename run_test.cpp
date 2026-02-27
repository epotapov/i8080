#include <iostream>

#include "I8080.h"

#define MEMORY_SIZE 0x10000

void run_test(const char * file, uint64_t expected) {
    I8080 i8080(MEMORY_SIZE, 0x100, file);
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
    std::cout << "Expected cycles: " << expected << std::endl;
    std::cout << "Ran cycles: " << i8080.cycle << std::endl;
}

int main(int argc, char** argv) {
    // run_test("test/TST8080.COM", 4924LU);
    run_test("test/CPUTEST.COM", 255653383LU);
    // run_test("test/8080PRE.COM", 7817LU);
    // run_test("test/8080EXM.COM", 23803381171LU);
    return 0;
}