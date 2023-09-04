//
// Created by lajua on 8/1/2021.
//

/*
 * =====================================================================================
 *
 *       Filename:  emu.h
 *          
 *    Description:  Header file for "emu.c". It contains the struct which defines the Chip8 system.
 *          Date:   8/1/2021
 *        Version:  1.0
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Lajuan Station 
 *    
 *
 * =====================================================================================
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef CHIP8_CHIP8_H
#define CHIP8_CHIP8_H

#define MEMORY_SIZE 4096
#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32
#define DISPLAY_SIZE DISPLAY_HEIGHT * DISPLAY_WIDTH
#define STACK_SIZE 16
#define NUM_KEYS 16 
#define NUM_REGISTERS 16


/* Struct which defines the Chip8 System */
typedef struct Chip8
{

    //Memory
    uint8_t memory[MEMORY_SIZE];

    //Display
    uint8_t display[DISPLAY_SIZE];

    //Program Counter
    uint16_t pc;

    //Index Register - Point at locations in memory
    uint16_t I;

    //Stack
    uint16_t stack[STACK_SIZE];

    //Stack Pointer
    uint16_t sp;

    //8-bit delay timer
    uint8_t delay_timer;

    //8-bit sound timer
    uint8_t sound_timer;

    //Current opcode
    uint16_t opcode;

    //Keys
    uint8_t key[NUM_KEYS];

    //General Purpose Registers V0 - VF
    uint8_t V[NUM_REGISTERS];

    //Halt flag
    uint8_t halt;

    //Draw Flag
    uint8_t drawFlag;

} Chip8;


//Function Declarations

/*
 * Function: loadProgram
 * -------------------
 * Loads rom into a buffer then loads rom from buffer 
 * into Chip8 memory starting at address 0x200
 * 
 * state: pointer to Chip8 struct
 * f: File Object created using rom file
 * fsize: size of the file
 */
void loadProgram(Chip8* s, FILE *f, int fsize);


/*
 * Function: InitChip8
 * -------------------
 * Initializes the Chip8 System
 * 
 * returns: pointer to Chip8 Struct
 */
Chip8* InitChip8(void);


/*
 * Function: emulateCycle
 * --------------------------------
 * Executes an Instruction
 * 
 * s: pointer to Chip8 struct
 */
void emulateCycle(Chip8* s);

/*
 * Function: printRegisters
 * ------------------------
 * Prints values of registers in Chip8 system to the console
 * 
 * s: pointer to Chip8 struct
 */
void printRegisters(Chip8* s);


/*
 * Function: printTimers
 * ---------------------
 * Prints values of delay and sound timers of Chip8 system to the console
 * 
 * s: pointer to Chip8 struct
 */
void printTimers(Chip8* s);


/*
 * Function: printStack
 * --------------------
 * Prints values on the stack of the Chip8 system to the console
 * 
 * s: pointer to Chip8 struct
 */
void printStack(Chip8* s);


/*
 * Function: printState
 * --------------------
 * Prints values of delay and sound timers of Chip8 system to the console
 * Prints values on the stack of the Chip8 system to the console
 * Prints values of registers in the Chip8 system to the console
 * 
 * s: pointer to Chip8 struct
 */
void printState(Chip8* s);

/*
 * Function: drawGraphics
 * ----------------------
 * Draws graphics to the screen of the Chip8
 *
 * s: pointer to Chip8 struct
 */
void drawGraphics(Chip8* s, int start_x, int start_y);

/*
 * Function: checkKeys
 * -------------------
 * Checks to see which keys are currently being pressed
 *
 * s: pointer to Chip8 struct
 */
 void checkKeys(Chip8 *s);

#endif //CHIP8_CHIP8_H
