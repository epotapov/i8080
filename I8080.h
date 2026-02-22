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
    uint16_t getBC();
    uint16_t getDE();
    uint16_t getHL();
    void setBC(uint16_t value);
    void setDE(uint16_t value);
    void setHL(uint16_t value);
    uint8_t readMem(uint16_t addr);
    uint16_t readWord(uint16_t addr);
    void writeMem(uint16_t addr, uint8_t value);
    void writeWord(uint16_t addr, uint16_t value);
    bool checkParity(uint8_t value);
    uint8_t increment(uint8_t value);
    uint8_t decrement(uint8_t value);
    void rlc();
    void dad(uint16_t value);
    void rrc();
    void ral();
    void rar();
    void add(uint8_t value, bool cy);
    void sub(uint8_t value, bool cy);
    void ana(uint8_t value);
    void xra(uint8_t value);
    void ora(uint8_t value);
    void cmp(uint8_t value);
    uint16_t pop();
    void push(uint16_t value);
    void ret();
    void retIf(bool condition);


    void readOpcode();

    uint16_t sp = 0;
    uint16_t pc = 0;
    uint8_t a = 0, b = 0, c = 0, d = 0,
            e = 0, h = 0, l = 0;
    uint8_t status = 0;
    bool sign = false, zero = false, half = false,
         parity = false, carry = false;

    uint8_t opcode = 0;

    std::array<uint8_t, MEMORY_SIZE> memory;

};

inline uint16_t I8080::getBC() {
    return (b << 8) | c;
}

inline uint16_t I8080::getDE() {
    return (d << 8) | e;
}

inline uint16_t I8080::getHL() {
    return (h << 8) | l;
}

inline void I8080::setBC(uint16_t value) {
    b = value >> 8;
    c = value & 0x00ff;
}

inline void I8080::setDE(uint16_t value) {
    d = value >> 8;
    e = value & 0x00ff;
}

inline void I8080::setHL(uint16_t value) {
    h = value >> 8;
    l = value & 0x00ff;
}

inline uint8_t I8080::readMem(uint16_t addr) {
    return memory[addr];
}

inline uint16_t I8080::readWord(uint16_t addr) {
    return memory[addr] | (memory[addr + 1] << 8);
}

inline void I8080::writeMem(uint16_t addr, uint8_t value) {
    memory[addr] = value;
}

inline void I8080::writeWord(uint16_t addr, uint16_t value) {
    memory[addr] = value & 0xff;
    memory[(uint16_t) (addr + 1)] = value >> 8;
}

inline bool I8080::checkParity(uint8_t value) {
    uint8_t total = 0;
    for (uint8_t i = 0; i < 8; ++i) {
        total += ((value >> i) & 1);
    }
    return total % 2 == 0;
}

inline uint8_t I8080::increment(uint8_t value) {
    uint8_t increment = value + 1;
    half = (increment & 0xf) == 0;
    zero = increment == 0;
    sign = increment >> 7;
    parity = checkParity(increment);
    return increment;
}

inline uint8_t I8080::decrement(uint8_t value) {
    uint8_t decrement = value - 1;
    half = (decrement & 0xf) == 0xf;
    zero = decrement == 0;
    sign = decrement >> 7;
    parity = checkParity(decrement);
    return decrement;
}

inline void I8080::rlc() {
    uint8_t prev = a;
    carry = prev >> 7;
    a <<= 1;
    a |= carry;
}

inline void I8080::dad(uint16_t value) {
    uint32_t result = (uint32_t) getHL() + (uint32_t) value;
    setHL(result & 0xFFFF);
    carry = result > 0xFFFF;
}

inline void I8080::rrc() {
    uint8_t prev = a;
    carry = prev & 0x1;
    a >>= 1;
    a |= (carry << 7);
}

inline void I8080::ral() {
    uint8_t prev = a;
    a <<= 1;
    a |= carry;
    carry = (prev >> 7);
}

inline void I8080::rar() {
    uint8_t prev = a;
    a >>= 1;
    a |= (carry << 7);
    carry = (prev & 0x1);
}

inline void I8080::add(uint8_t value, bool cy) {
    uint8_t carry_in = (cy && carry) ? 1 : 0;
    uint16_t result = (uint16_t) a + (uint16_t) value + carry_in;
    half = ((a & 0x0F) + (value & 0x0F) + carry_in) > 0x0F;
    carry = result > 0xFF;
    a = (uint8_t) result & 0xff;
    zero = a == 0;
    sign = a >> 7;
    parity = checkParity(a);
}

inline void I8080::sub(uint8_t value, bool cy) {
    uint8_t prev = a;
    uint8_t borrow_in = (cy && carry) ? 1 : 0;

    carry = !borrow_in;
    add((uint8_t) ~value, true);

    carry = !carry;
    half = (prev & 0x0F) < ((value & 0x0F) + borrow_in);
}

inline void I8080::ana(uint8_t value) {
    uint8_t result = a & value;
    carry = false;
    half = ((a | value) & 0x08) != 0; // maybe clear
    zero = a == 0;
    sign = a >> 7;
    parity = checkParity(a);
    a = result;
}

inline void I8080::xra(uint8_t value) {
    a ^= value;
    carry = false;
    half = false;
    zero = a == 0;
    sign = a >> 7;
    parity = checkParity(a);
}

inline void I8080::ora(uint8_t value) {
    a |= value;
    carry = false;
    half = false;
    zero = a == 0;
    sign = a >> 7;
    parity = checkParity(a);
}

inline void I8080::cmp(uint8_t value) {
    uint8_t result = a - value;
    carry = a < value;
    half = (a & 0x0F) < (value & 0x0F);
    zero = result == 0;
    sign = result >> 7;
    parity = checkParity(result);
}

inline uint16_t I8080::pop() {
    uint16_t word = readWord(sp);
    sp += 2;
    return word;
}

inline void I8080::push(uint16_t value) {
    sp -= 2;
    writeWord(sp, value);
}

inline void I8080::ret() {
    pc = pop();
}

inline void I8080::retIf(bool condition) {
    if (condition) {
        ret();
        // Cycle
    }
}

#endif