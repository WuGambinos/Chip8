#include <stdint.h>
#include "emu.h"
#ifndef CHIP8_INS
#define CHIP8_INS

void Op0(Chip8* s, uint16_t opcode);

/*
 * Function: Op1
 * -------------
 * 1NNN - JMP NNN
 * Sets Program Counter to NNN
 *
 * s: pointer to Chip8 struct
 * opcode: 1NNN
 *
 */
void Op1(Chip8 *s, uint16_t opcode);

/*
 * Function: Op2
 * -------------
 * 2NNN - CALL NNN
 * Increments stack pointer, then puts the current PC on top of the stack
 * PC is then set to NNN
 *
 * s: pointer to Chip8 struct
 * opcode: 2NNN
 */
void Op2(Chip8 *s, uint16_t opcode);

/*
 * Function: Op3
 * -------------
 * 3XNN - Skip if VX == NN
 * Skip next instruction if value in register VX is equal to NN 
 *
 * s: pointer to Chip8 struct
 * opcode: 3XNN
 */
void Op3(Chip8 *s, uint16_t opcode);

/*
 * Function: Op4
 * -------------
 * 4XNN - Skip if VX != NN
 * Skip next instruction if value in register VX is not equal to NN
 * 
 * s: pointer to Chip8 struct
 * opcode: 4XNN
 */
void Op4(Chip8 *s, uint16_t opcode);

/*
 * Function: Op5
 * -------------
 * 5XY0 - Skip if VX == VY
 * Skip next instruction if value in register VX is equal to value in register VY
 * 
 * s: pointer to Chip8 struct
 * opcode: 5XY0
 */
void Op5(Chip8 *s, uint16_t opcode);

/*
 * Function: Op6
 * -------------
 * 6XNN - VX = NN
 * Store value NN in register VX
 *
 * s: pointer to Chip8 struct
 * opcode: 6XNN
 */
void Op6(Chip8 *s, uint16_t opcode);

/*
 * Function: Op7
 * -------------
 * 7XKK - VX += NN
 * Add value NN to register VX
 * 
 *
 * s: pointer to Chip8 struct
 * opcode: 2NNN
 */
void Op7(Chip8 *s, uint16_t opcode);

/*
 * Function: Op8
 * -------------
 * This function contains multiple opcodes within it
 * 
 * 8XY0 - VX = VY
 * Store value of register VY in VX 
 *
 * 8XY1 - VX = VX | VY
 * Set register VX to the logical or of register VX and register VY
 * 
 * 8XY2 - VX = VX & VY
 * Set register VX to the logical and of register VX and register VY
 * 
 * 8XY3 - VX == VX  ^ VY
 * Set register VX to the logical xor of register VX and register VY
 *
 * 8XY4 - VX = VX + VY, VF = carry
 * Add value of VY to register VX
 * Set VF if carry occurs
 * clear VF is carry does not occur
 *
 * 8XY5 - VX = VX - VY, set VF = NOT borrow
 * Subtract valeu of register VY from register VX
 * Clear VF if a borrow occurs
 * Set VF if a borrow does not occurs
 *
 * 8XY6 - VX = VX >> 1
 * Store the value of register VY shifted right one bit in register VX
 * Set register VF to LSB of VX prior to shift
 * 
 * 8XY7 - VX = VY - VX, set VF = NOT borrow
 * Set register VX to teh value of VY - VX
 * Clear VF if borrow occurs
 * Set VF if borrow does not occur
 *
 * 8XYE - Store value of register VY shifted left by one bit in register VX
 * Set register VF to the MSB of VX prior to Shift
 */

void Op8(Chip8 *s, uint16_t opcode);
void Op9(Chip8 *s, uint16_t opcode);
void OpA(Chip8 *s, uint16_t opcode);
void OpB(Chip8 *s, uint16_t opcode);
void OpC(Chip8 *s, uint16_t opcode);
void OpD(Chip8 *s, uint16_t opcode);
void OpE(Chip8 *s, uint16_t opcode);
void OpF(Chip8 *s, uint16_t opcode);

#endif