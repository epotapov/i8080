#ifndef I8080_H
#define I8080_H

#include <cstdint>
#include <array>

#define MEMORY_SIZE 0x10000

static const uint8_t OPCODES_CYCLES[256] = {
//  0  1   2   3   4   5   6   7   8  9   A   B   C   D   E  F
    4, 10, 7,  5,  5,  5,  7,  4,  4, 10, 7,  5,  5,  5,  7, 4,  // 0
    4, 10, 7,  5,  5,  5,  7,  4,  4, 10, 7,  5,  5,  5,  7, 4,  // 1
    4, 10, 16, 5,  5,  5,  7,  4,  4, 10, 16, 5,  5,  5,  7, 4,  // 2
    4, 10, 13, 5,  10, 10, 10, 4,  4, 10, 13, 5,  5,  5,  7, 4,  // 3
    5, 5,  5,  5,  5,  5,  7,  5,  5, 5,  5,  5,  5,  5,  7, 5,  // 4
    5, 5,  5,  5,  5,  5,  7,  5,  5, 5,  5,  5,  5,  5,  7, 5,  // 5
    5, 5,  5,  5,  5,  5,  7,  5,  5, 5,  5,  5,  5,  5,  7, 5,  // 6
    7, 7,  7,  7,  7,  7,  7,  7,  5, 5,  5,  5,  5,  5,  7, 5,  // 7
    4, 4,  4,  4,  4,  4,  7,  4,  4, 4,  4,  4,  4,  4,  7, 4,  // 8
    4, 4,  4,  4,  4,  4,  7,  4,  4, 4,  4,  4,  4,  4,  7, 4,  // 9
    4, 4,  4,  4,  4,  4,  7,  4,  4, 4,  4,  4,  4,  4,  7, 4,  // A
    4, 4,  4,  4,  4,  4,  7,  4,  4, 4,  4,  4,  4,  4,  7, 4,  // B
    5, 10, 10, 10, 11, 11, 7,  11, 5, 10, 10, 10, 11, 17, 7, 11, // C
    5, 10, 10, 10, 11, 11, 7,  11, 5, 10, 10, 10, 11, 17, 7, 11, // D
    5, 10, 10, 18, 11, 11, 7,  11, 5, 5,  10, 4,  11, 17, 7, 11, // E
    5, 10, 10, 4,  11, 11, 7,  11, 5, 5,  10, 4,  11, 17, 7, 11  // F
};

struct I8080 {
    I8080();
    ~I8080() = default;

    // Helpers
    inline uint16_t getBC() {
        return (b << 8) | c;
    }
    
    inline uint16_t getDE() {
        return (d << 8) | e;
    }
    
    inline uint16_t getHL() {
        return (h << 8) | l;
    }
    
    inline void setBC(uint16_t value) {
        b = value >> 8;
        c = value & 0x00ff;
    }
    
    inline void setDE(uint16_t value) {
        d = value >> 8;
        e = value & 0x00ff;
    }
    
    inline void setHL(uint16_t value) {
        h = value >> 8;
        l = value & 0x00ff;
    }
    
    inline uint8_t readMem(uint16_t addr) {
        return memory[addr];
    }

    inline uint16_t readWord(uint16_t addr) {
        return memory[addr] | (memory[addr + 1] << 8);
    }
    
    inline void writeMem(uint16_t addr, uint8_t value) {
        memory[addr] = value;
    }

    inline uint8_t increment(uint8_t value) {
        //TODO
        return 0;
    }

    inline void add(uint8_t* first, uint8_t* second) {
        //TODO
        return;
    }


    void readOpcode();

    uint16_t sp = 0;
    uint16_t pc = 0;
    uint8_t a = 0, b = 0, c = 0, d = 0,
            e = 0, h = 0, l = 0;
    uint8_t status = 0;
    bool sign, zero, ac, parity, carry;

    uint8_t opcode = 0;

    std::array<uint8_t, MEMORY_SIZE> memory;

};

#endif