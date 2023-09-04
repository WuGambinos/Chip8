/*
 * =====================================================================================
 *
 *       Filename:  emu.c
 *
 *    Description:
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

#include "../include/emu.h"

#include <stdio.h>
#include <stdlib.h>

#include "../include/disassemble.h"
#include "../include/font.h"
#include "../include/instruction.h"
#include "../include/raylib.h"

#define RECT_SIZE 5
#define PC_START 0x200

/*
 * Function: init_chip8
 * -------------------
 * Initializes the Chip8 System
 */
Chip8* init_chip8(void) {
    Chip8* s = (Chip8*) calloc(sizeof(Chip8), 1);

    s->pc = PC_START;
    s->opcode = 0;
    s->sp = 0;
    s->I = 0;
    s->halt = 0;
    s->drawFlag = 1;

    for (int i = 0; i < 0x50; i++) {
        s->memory[i] = font[i];
    }

    return s;
}

void check_keys(Chip8* s) {
    s->key[0x1] = IsKeyPressed(KEY_ONE) || IsKeyDown(KEY_ONE);
    s->key[0x2] = IsKeyPressed(KEY_TWO) || IsKeyDown(KEY_TWO);
    s->key[0x3] = IsKeyPressed(KEY_THREE) || IsKeyDown(KEY_THREE);
    s->key[0xC] = IsKeyPressed(KEY_FOUR) || IsKeyDown(KEY_FOUR);
    s->key[0x4] = IsKeyPressed(KEY_Q) || IsKeyDown(KEY_Q);
    s->key[0x5] = IsKeyPressed(KEY_W) || IsKeyDown(KEY_W);
    s->key[0x6] = IsKeyPressed(KEY_E) || IsKeyDown(KEY_E);
    s->key[0xD] = IsKeyPressed(KEY_R) || IsKeyDown(KEY_R);
    s->key[0x7] = IsKeyPressed(KEY_A) || IsKeyDown(KEY_A);
    s->key[0x8] = IsKeyPressed(KEY_S) || IsKeyDown(KEY_S);
    s->key[0x9] = IsKeyPressed(KEY_D) || IsKeyDown(KEY_D);
    s->key[0xE] = IsKeyPressed(KEY_F) || IsKeyDown(KEY_F);
    s->key[0xA] = IsKeyPressed(KEY_Z) || IsKeyDown(KEY_Z);
    s->key[0x0] = IsKeyPressed(KEY_X) || IsKeyDown(KEY_X);
    s->key[0xB] = IsKeyPressed(KEY_C) || IsKeyDown(KEY_C);
    s->key[0xF] = IsKeyPressed(KEY_V) || IsKeyDown(KEY_V);
}

void draw_graphics(Chip8* s, int start_x, int start_y) {
    for (int y = 0; y < DISPLAY_HEIGHT; ++y) {
        for (int x = 0; x < DISPLAY_WIDTH; ++x) {
            if (s->display[(y * DISPLAY_WIDTH) + x] != 0) {
                DrawRectangle((x * RECT_SIZE) + start_x,
                              (y * RECT_SIZE) + start_y, RECT_SIZE, RECT_SIZE,
                              WHITE);
            } else {
                DrawRectangle((x * RECT_SIZE) + start_x,
                              (y * RECT_SIZE) + start_y, RECT_SIZE, RECT_SIZE,
                              BLACK);
            }
        }
    }
}

// Load Program into memory
void load_program(Chip8* s, FILE* f, int fsize) {
    uint8_t* buffer = (uint8_t*) malloc(fsize + PC_START);
    fread(buffer + PC_START, fsize, 1, f);
    fclose(f);

    for (int i = 0; i < fsize; i++) {
        s->memory[i + PC_START] = buffer[i + PC_START];
    }
}

/*
 * Fetch opcode
 * Decode opcode
 * Execute opcode
 */
void emulate_cycle(Chip8* s) {
    uint16_t opcode = (s->memory[s->pc] << 8) | (s->memory[(s->pc) + 1]);
    uint16_t firstByte = opcode & 0xF000;

    switch (firstByte) {
        case 0x0000:
            op_0(s, opcode);
            break;

        // Jump to NNN
        case 0x1000:
            op_1(s, opcode);
            break;

        case 0x2000:
            op_2(s, opcode);
            break;

        // Skip if VX == NN
        case 0x3000:
            op_3(s, opcode);
            break;

        // Skip if VX != NN
        case 0x4000:
            op_4(s, opcode);
            break;

        // Skip if VX == VY
        case 0x5000:
            op_5(s, opcode);
            break;

        // Store NN in VX
        case 0x6000:
            op_6(s, opcode);
            break;

        // Add the value NN to register VX
        case 0x7000:
            op_7(s, opcode);
            break;

        // Set VX to VY
        case 0x8000:
            op_8(s, opcode);
            break;

        // Skip if VX != VY
        case 0x9000:
            op_9(s, opcode);
            break;

        // ANNN: Sets I to the address NNN
        case 0xA000:
            op_a(s, opcode);
            break;

        // PC = V0 + NNN
        case 0xB000:
            op_b(s, opcode);
            break;

        case 0xC000:
            op_c(s, opcode);
            break;

        // Draws Sprite at coordinate (VX, VY)
        case 0xD000:
            op_d(s, opcode);
            break;

        case 0xE000:
            op_e(s, opcode);
            break;

        case 0xF000:
            op_f(s, opcode);
            break;

        default:
            printf("Unknwon opcode 0x%X\n", opcode);
    }

    if (s->delay_timer > 0) {
        --(s->delay_timer);
    }

    if (s->sound_timer > 0) {
        if (s->sound_timer == 1) {
            printf("BEEP\n");
            --(s->sound_timer);
        }
    }
}

void print_state(Chip8* s) {
    print_registers(s);
    print_stack(s);
    print_timers(s);
}

void print_timers(Chip8* s) {
    printf("Delay Timer: %X\n", s->delay_timer);
    printf("Sound Timer: %X\n", s->sound_timer);
    printf("\n");
}

void print_stack(Chip8* s) {
    printf("STACK\n");
    for (int i = 0; i < STACK_SIZE; i++) {
        printf("Stack[%X] = %X \n", i, s->stack[i]);
    }

    printf("\n");
}

void print_registers(Chip8* s) {
    printf("REGISTERS\n");
    for (int i = 0; i < NUM_REGISTERS; i++) {
        printf("V[%X] = %X \n", i, s->V[i]);
    }

    printf("\n");
}
