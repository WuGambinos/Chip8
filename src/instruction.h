#ifndef CHIP8_INS
#define CHIP8_INS

void Op0(Chip8* s, uint16_t opcode);
void Op1(Chip8 *s, uint16_t opcode);
void Op2(Chip8 *s, uint16_t opcode);
void Op3(Chip8 *s, uint16_t opcode);
void Op4(Chip8 *s, uint16_t opcode);
void Op5(Chip8 *s, uint16_t opcode);
void Op6(Chip8 *s, uint16_t opcode);
void Op7(Chip8 *s, uint16_t opcode);
void Op8(Chip8 *s, uint16_t opcode);
void Op9(Chip8 *s, uint16_t opcode);
void OpA(Chip8 *s, uint16_t opcode);
void OpB(Chip8 *s, uint16_t opcode);
void OpC(Chip8 *s, uint16_t opcode);
void OpD(Chip8 *s, uint16_t opcode);
void OpE(Chip8 *s, uint16_t opcode);
void OpF(Chip8 *s, uint16_t opcode);

#endif