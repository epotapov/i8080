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
        case 0x04: break; //TODO
        case 0x05: break; //TODO
        case 0x06:
            b = readMem(pc);
            pc++;
            break;
        case 0x07: break; //TODO
        case 0x08: break;
        case 0x09: break; //TODO
        case 0x0a: a = readMem(getBC()); break;
        case 0x0b: setBC(getBC() - 1); break;
        case 0x0c: break; //TODO
        case 0x0d: break; //TODO
        case 0x0e:
            c = readMem(pc);
            pc++;
            break;
        case 0x0f: break; //TODO
        case 0x10: break;
        case 0x11: 
            setDE(readWord(pc));
            pc += 2;
            break;
        case 0x12: writeMem(getDE(), a); break;
        case 0x13: setDE(getDE() + 1); break;
        case 0x14: break; //TODO
        case 0x15: break; //TODO
        case 0x16:
            d = readMem(pc);
            pc++;
            break;
        case 0x17: break; //TODO
        case 0x18: break;
        case 0x19: break; //TODO
        case 0x1a: a = readMem(getDE()); break;
        case 0x1b: setDE(getDE() - 1); break;
        case 0x1c: break; //TODO
        case 0x1d: break; //TODO
        case 0x1e:
            e = readMem(pc);
            pc++;
            break;
        case 0x1f: break; //TODO
        case 0x20: break;
        case 0x21: 
            setHL(readWord(pc));
            pc += 2;
            break;
        case 0x22: break; //TODO

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
    }


}

int main(int argc, char** argv) {
    return 0;
}