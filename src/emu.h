//
// Created by lajua on 8/1/2021.
//
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef CHIP8_CHIP8_H
#define CHIP8_CHIP8_H


typedef struct Chip8
{

    //Memory
    uint8_t memory[4096];

    //Display
    uint8_t display[64 * 32];

    //Program Counter
    uint16_t pc;

    //Index Register - Point at locations in memory
    uint16_t I;

    //Stack
    uint16_t stack[16];

    //Stack Pointer
    uint16_t sp;

    //8-bit delay timer
    uint8_t delay_timer;

    //8-bit sound timer
    uint8_t sound_timer;

    //Current opcode
    uint16_t opcode;

    //Keys
    uint8_t key[16];

    //General Purpose Registers V0 - VF
    uint8_t V[16];

    uint8_t halt;

    uint8_t drawFlag;

} Chip8;

//Function Declarations
void loadProgram(Chip8* state, FILE *f, int fsize);
Chip8* InitChip8(void);
void emulateCycle(Chip8* s);
void DisassembleChip8Op(uint8_t *codebuffer, int pc);
void printRegisters(Chip8* s);
void printTimers(Chip8* s);
void printStack(Chip8* s);
void printState(Chip8* s);
void drawGraphics(Chip8* s);

#endif //CHIP8_CHIP8_H
