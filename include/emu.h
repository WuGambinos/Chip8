//
// Created by lajua on 8/1/2021.
//

/*
 * =====================================================================================
 *
 *       Filename:  emu.h
 *
 *    Description:  Header file for "emu.c". It contains the struct which
 * defines the Chip8 system. Date:   8/1/2021 Version:  1.0 Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Lajuan Station
 *
 *
 * =====================================================================================
 */
#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 4096
#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32
#define DISPLAY_SIZE DISPLAY_HEIGHT* DISPLAY_WIDTH
#define STACK_SIZE 16
#define NUM_KEYS 16
#define NUM_REGISTERS 16

typedef struct Chip8 {
    uint8_t memory[MEMORY_SIZE];
    uint8_t display[DISPLAY_SIZE];
    uint16_t pc;
    uint16_t I;
    uint16_t stack[STACK_SIZE];
    uint16_t sp;
    uint8_t delay_timer;
    uint8_t sound_timer;
    uint16_t opcode;
    uint8_t key[NUM_KEYS];

    // General Purpose Registers V0 - VF
    uint8_t V[NUM_REGISTERS];
    uint8_t halt;
    uint8_t drawFlag;
} Chip8;

// Function Declarations
/*
 * Function: init_chip8
 * -------------------
 * Initializes the Chip8 System
 *
 * returns: pointer to Chip8 Struct
 */
Chip8* init_chip8(void);

/*
 * Function: check_keys
 * -------------------
 * Checks to see which keys are currently being pressed
 *
 * s: pointer to Chip8 struct
 */
void check_keys(Chip8* s);

/*
 * Function: load_program
 * -------------------
 * Loads rom into a buffer then loads rom from buffer
 * into Chip8 memory starting at address 0x200
 *
 * state: pointer to Chip8 struct
 * f: File Object created using rom file
 * fsize: size of the file
 */
void load_program(Chip8* s, FILE* f, int fsize);

/*
 * Function: emulate_cycle
 * --------------------------------
 * Executes an Instruction
 *
 * s: pointer to Chip8 struct
 */
void emulate_cycle(Chip8* s);

/*
 * Function: draw_graphics
 * ----------------------
 * Draws graphics to the screen of the Chip8
 *
 * s: pointer to Chip8 struct
 */
void draw_graphics(Chip8* s, int start_x, int start_y);

/*
 * Function: print_registers
 * ------------------------
 * Prints values of registers in Chip8 system to the console
 *
 * s: pointer to Chip8 struct
 */
void print_registers(Chip8* s);

/*
 * Function: print_timers
 * ---------------------
 * Prints values of delay and sound timers of Chip8 system to the console
 *
 * s: pointer to Chip8 struct
 */
void print_timers(Chip8* s);

/*
 * Function: print_stack
 * --------------------
 * Prints values on the stack of the Chip8 system to the console
 *
 * s: pointer to Chip8 struct
 */
void print_stack(Chip8* s);

/*
 * Function: print_state
 * --------------------
 * Prints values of delay and sound timers of Chip8 system to the console
 * Prints values on the stack of the Chip8 system to the console
 * Prints values of registers in the Chip8 system to the console
 *
 * s: pointer to Chip8 struct
 */
void print_state(Chip8* s);
