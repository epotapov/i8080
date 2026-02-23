#include "I8080.h"

I8080::I8080() {
    
}

void I8080::readOpcode() {
    uint8_t opcode = readMem(pc);
    pc++;

    switch (opcode) {
        case 0x00: break;
        case 0x01:
            setBC(readWord(pc));
            pc += 2;
            break;
        case 0x02: writeMem(getBC(), a); break;
        case 0x03: setBC(getBC() + 1); break;
        case 0x04: b = increment(b); break;
        case 0x05: b = decrement(b); break;
        case 0x06:
            b = readMem(pc);
            pc++;
            break;
        case 0x07: rlc(); break;
        case 0x08: break;
        case 0x09: dad(getBC()); break;
        case 0x0a: a = readMem(getBC()); break;
        case 0x0b: setBC(getBC() - 1); break;
        case 0x0c: c = increment(c); break;
        case 0x0d: c = decrement(c); break;
        case 0x0e:
            c = readMem(pc);
            pc++;
            break;
        case 0x0f: rrc(); break;
        case 0x10: break;
        case 0x11: 
            setDE(readWord(pc));
            pc += 2;
            break;
        case 0x12: writeMem(getDE(), a); break;
        case 0x13: setDE(getDE() + 1); break;
        case 0x14: d = increment(d); break;
        case 0x15: d = decrement(d); break;
        case 0x16:
            d = readMem(pc);
            pc++;
            break;
        case 0x17: ral(); break;
        case 0x18: break;
        case 0x19: dad(getDE()); break;
        case 0x1a: a = readMem(getDE()); break;
        case 0x1b: setDE(getDE() - 1); break;
        case 0x1c: e = increment(e); break;
        case 0x1d: e = decrement(e); break;
        case 0x1e:
            e = readMem(pc);
            pc++;
            break;
        case 0x1f: rar(); break;
        case 0x20: break;
        case 0x21: 
            setHL(readWord(pc));
            pc += 2;
            break;
        case 0x22: {
            uint16_t addr = readWord(pc);
            pc += 2;
            writeMem(addr, l);
            writeMem(addr + 1, h);
            break;
        }
        case 0x23: setHL(getHL() + 1); break;
        case 0x24: h = increment(h); break;
        case 0x25: h = decrement(h); break;
        case 0x26:
            h = readMem(pc);
            pc++;
            break;
        case 0x27: break; //TODO
        case 0x28: break;
        case 0x29: dad(getHL()); break;
        case 0x2a: {
            uint16_t addr = readWord(pc);
            pc += 2;
            l = readMem(addr);
            h = readMem(addr + 1);
            break;
        }
        case 0x2b: setHL(getHL() - 1); break;
        case 0x2c: l = increment(l); break;
        case 0x2d: l = decrement(l); break;
        case 0x2e:
            l = readMem(pc);
            pc++;
            break;
        case 0x2f: a = ~a; break;
        case 0x30: break;
        case 0x31: 
            sp = readWord(pc);
            pc += 2; 
            break;
        case 0x32: {
            uint16_t addr = readWord(pc);
            pc += 2;
            writeMem(addr, a);
            break;
        }
        case 0x33: sp++; break;
        case 0x34: {
            uint8_t value = readMem(getHL());
            value = increment(value);
            writeMem(getHL(), value);
            break;
        }
        case 0x35: {
            uint8_t value = readMem(getHL());
            value = decrement(value);
            writeMem(getHL(), value);
            break;
        }
        case 0x36: writeMem(getHL(), readMem(pc++)); break;
        case 0x37: carry = 1; break;
        case 0x38: break;
        case 0x39: dad(sp); break;
        case 0x3a: {
            uint16_t addr = readWord(pc);
            pc += 2;
            a = readMem(addr);
            break;
        }
        case 0x3b: sp--; break;
        case 0x3c: a = increment(a); break;
        case 0x3d: a = decrement(a); break;
        case 0x3e:
            a = readMem(pc);
            pc++;
            break;
        case 0x3f: carry = !carry; break;
        case 0x40: b = b; break;
        case 0x41: b = c; break;
        case 0x42: b = d; break;
        case 0x43: b = e; break;
        case 0x44: b = h; break;
        case 0x45: b = l; break;
        case 0x46: b = readMem(getHL()); break;
        case 0x47: b = a; break;
        case 0x48: c = b; break;
        case 0x49: c = c; break;
        case 0x4a: c = d; break;
        case 0x4b: c = e; break;
        case 0x4c: c = h; break;
        case 0x4d: c = l; break;
        case 0x4e: c = readMem(getHL()); break;
        case 0x4f: c = a; break;
        case 0x50: d = b; break;
        case 0x51: d = c; break;
        case 0x52: d = d; break;
        case 0x53: d = e; break;
        case 0x54: d = h; break;
        case 0x55: d = l; break;
        case 0x56: d = readMem(getHL()); break;
        case 0x57: d = a; break;
        case 0x58: e = b; break;
        case 0x59: e = c; break;
        case 0x5a: e = d; break;
        case 0x5b: e = e; break;
        case 0x5c: e = h; break;
        case 0x5d: e = l; break;
        case 0x5e: e = readMem(getHL()); break;
        case 0x5f: e = a; break;
        case 0x60: h = b; break;
        case 0x61: h = c; break;
        case 0x62: h = d; break;
        case 0x63: h = e; break;
        case 0x64: h = h; break;
        case 0x65: h = l; break;
        case 0x66: h = readMem(getHL()); break;
        case 0x67: h = a; break;
        case 0x68: l = b; break;
        case 0x69: l = c; break;
        case 0x6a: l = d; break;
        case 0x6b: l = e; break;
        case 0x6c: l = h; break;
        case 0x6d: l = l; break;
        case 0x6e: l = readMem(getHL()); break;
        case 0x6f: l = a; break;
        case 0x70: writeMem(getHL(), b); break;
        case 0x71: writeMem(getHL(), c); break;
        case 0x72: writeMem(getHL(), d); break;
        case 0x73: writeMem(getHL(), e); break;
        case 0x74: writeMem(getHL(), h); break;
        case 0x75: writeMem(getHL(), l); break;
        case 0x76: break; //HLT
        case 0x77: writeMem(getHL(), a); break;
        case 0x78: a = b; break;
        case 0x79: a = c; break;
        case 0x7a: a = d; break;
        case 0x7b: a = e; break;
        case 0x7c: a = h; break;
        case 0x7d: a = l; break;
        case 0x7e: a = readMem(getHL()); break;
        case 0x7f: a = a; break;
        case 0x80: add(b, false); break;
        case 0x81: add(c, false); break;
        case 0x82: add(d, false); break;
        case 0x83: add(e, false); break;
        case 0x84: add(h, false); break;
        case 0x85: add(l, false); break;
        case 0x86: add(readMem(getHL()), false); break;
        case 0x87: add(a, false); break;
        case 0x88: add(b, true); break;
        case 0x89: add(c, true); break;
        case 0x8a: add(d, true); break;
        case 0x8b: add(e, true); break;
        case 0x8c: add(h, true); break;
        case 0x8d: add(l, true); break;
        case 0x8e: add(readMem(getHL()), true); break;
        case 0x8f: add(a, true); break;
        case 0x90: sub(b, false); break;
        case 0x91: sub(c, false); break;
        case 0x92: sub(d, false); break;
        case 0x93: sub(e, false); break;
        case 0x94: sub(h, false); break;
        case 0x95: sub(l, false); break;
        case 0x96: sub(readMem(getHL()), false); break;
        case 0x97: sub(a, false); break;
        case 0x98: sub(b, true); break;
        case 0x99: sub(c, true); break;
        case 0x9a: sub(d, true); break;
        case 0x9b: sub(e, true); break;
        case 0x9c: sub(h, true); break;
        case 0x9d: sub(l, true); break;
        case 0x9e: sub(readMem(getHL()), true); break;
        case 0x9f: sub(a, true); break;
        case 0xa0: ana(b); break;
        case 0xa1: ana(c); break;
        case 0xa2: ana(d); break;
        case 0xa3: ana(e); break;
        case 0xa4: ana(h); break;
        case 0xa5: ana(l); break;
        case 0xa6: ana(readMem(getHL())); break;
        case 0xa7: ana(a); break;
        case 0xa8: xra(b); break;
        case 0xa9: xra(c); break;
        case 0xaa: xra(d); break;
        case 0xab: xra(e); break;
        case 0xac: xra(h); break;
        case 0xad: xra(l); break;
        case 0xae: xra(readMem(getHL())); break;
        case 0xaf: xra(a); break;
        case 0xb0: ora(b); break;
        case 0xb1: ora(c); break;
        case 0xb2: ora(d); break;
        case 0xb3: ora(e); break;
        case 0xb4: ora(h); break;
        case 0xb5: ora(l); break;
        case 0xb6: ora(readMem(getHL())); break;
        case 0xb7: ora(a); break;
        case 0xb8: cmp(b); break;
        case 0xb9: cmp(c); break;
        case 0xba: cmp(d); break;
        case 0xbb: cmp(e); break;
        case 0xbc: cmp(h); break;
        case 0xbd: cmp(l); break;
        case 0xbe: cmp(readMem(getHL())); break;
        case 0xbf: cmp(a); break;
        case 0xc0: retIf(zero == false); break;
        case 0xc1: setBC(pop()); break;
        case 0xc2: jmp(zero == false); break;
        case 0xc3: jmp(true); break;
        case 0xc4: call(zero == false); break;
        case 0xc5: push(getBC()); break;
        case 0xc6: {
            uint8_t value = readMem(pc);
            pc++;
            add(value, false);
            break;
        }
        case 0xc7: call((uint16_t) 0x00); break;
        case 0xc8: retIf(zero == true); break;
        case 0xc9: ret(); break;
        case 0xca: jmp(zero == true); break;
        case 0xcb: break;
        case 0xcc: call(zero == true); break;
        case 0xcd: {
            uint16_t addr = readWord(pc);
            pc += 2;
            call(addr);
            break;
        }
        case 0xce: {
            uint8_t value = readMem(pc);
            pc++;
            add(value, true);
            break;
        }
        case 0xcf: call((uint16_t) 0x08); break;
        case 0xd0: retIf(carry == false); break;
        case 0xd1: setDE(pop()); break;
        case 0xd2: jmp(carry == false); break;
        case 0xd3: break; //TODO
        case 0xd4: call(carry == false); break;
        case 0xd5: push(getDE()); break;
        case 0xd6: {
            uint8_t value = readMem(pc);
            pc++;
            sub(value, false);
            break;
        }
        case 0xd7: call((uint16_t) 0x10); break;
        case 0xd8: retIf(carry == true); break;
        case 0xd9: break;
        case 0xda: jmp(carry == true); break;
        case 0xdb: break; //TODO
        case 0xdc: call(carry == true); break;
        case 0xdd: break;
        case 0xde: {
            uint8_t value = readMem(pc);
            pc++;
            sub(value, true);
            break;
        }
        case 0xdf: call((uint16_t) 0x18); break;

    }


}

int main(int argc, char** argv) {
    return 0;
}