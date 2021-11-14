
#ifndef CHIP8_DIS
#define CHIP8_DIS

/*
 * Function: DisassembleChip80p
 * ----------------------------
 * Disassembles opcode for rom of Chip8 System
 * codebuffer: buffer that holds the opcodes for the given rom
 * pc: Program Counter
 */
void DisassembleChip8Op(uint8_t *codebuffer, int pc);

#endif