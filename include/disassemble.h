#pragma once
#include <stdint.h>

/*
 * Function: DisassembleChip80p
 * ----------------------------
 * Disassembles opcode for rom of Chip8 System
 * codebuffer: buffer that holds the opcodes for the given rom
 * pc: Program Counter
 */
void dissasemble_opcodes(uint8_t* codebuffer, int pc);
