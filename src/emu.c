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

#include "emu.h"
#include "font.h"
#include "../include/raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "disassemble.h"

/*
 * Function: InitChip8
 * -------------------
 * Initializes the Chip8 System
 * 
 * 
 * 
 */
Chip8* InitChip8(void)
{
    //Create Chip
    Chip8* s  = (Chip8*) calloc(sizeof(Chip8), 1);

    //Program counter starts at 0x200
    s -> pc = 0x200;    

    //Reset current opcode
    s -> opcode = 0;   

    //Reset index register
    s -> sp = 0;

    //Reset stack pointer
    s -> I = 0;

    //Clear halt flag
    s -> halt = 0;

    //Clear draw flag
    s -> drawFlag = 1;

    //Load fontset
    for(int i = 0; i < 0x50; i++)
    {
        s -> memory[i] = font[i];
    }



    return s;
}

void checkKeys(Chip8 *s)
{
    if(IsKeyPressed(KEY_ONE) || IsKeyDown(KEY_ONE))
    {
        s -> key[0x1] = 1;
    }

    else
    {
        s -> key[0x1] = 0;

    }



    if(IsKeyPressed(KEY_TWO) || IsKeyDown(KEY_TWO))
    {
        s -> key[0x2] = 1;

    }

    else
    {
        s -> key[0x2] = 0;

    }

    if(IsKeyPressed(KEY_THREE) || IsKeyDown(KEY_THREE))
    {
        s -> key[0x3] = 1;
    }

    else
    {
        s -> key[0x3] = 0;
    }

    if(IsKeyPressed(KEY_FOUR) || IsKeyDown(KEY_FOUR))
    {
        s -> key[0xC] = 1;

    }

    else
    {
        s -> key[0xC] = 0;

    }

    if(IsKeyPressed(KEY_Q) || IsKeyDown(KEY_Q))
    {
        s -> key[0x4] = 1;
    }

    else
    {
        s -> key[0x4] = 0;
    }

    if(IsKeyPressed(KEY_W) || IsKeyDown(KEY_W))
    {
        s -> key[0x5] = 1;
    }

    else
    {
        s -> key[0x5] = 0;
    }

    if(IsKeyPressed(KEY_E) || IsKeyDown(KEY_E))
    {
        s -> key[0x6] = 1;
    }

    else
    {
        s -> key[0x6] = 0;
    }

    if(IsKeyPressed(KEY_R) || IsKeyDown(KEY_R))
    {
        s -> key[0xD] = 1;
    }

    else
    {
        s -> key[0xD] = 0;
    }

    if(IsKeyPressed(KEY_A) || IsKeyDown(KEY_A))
    {
        s -> key[0x7] = 1;
    }

    else
    {
        s -> key[0x7] = 0;

    }

    if(IsKeyPressed(KEY_S) || IsKeyDown(KEY_S))
    {
        s -> key[0x8] = 1;

    }

    else
    {
        s -> key[0x8] = 0;

    }

    if(IsKeyPressed(KEY_D) || IsKeyDown(KEY_D))
    {
        s -> key[0x9] = 1;
    }

    else
    {
        s -> key[0x9] = 0;

    }

    if(IsKeyPressed(KEY_F) || IsKeyDown(KEY_F))
    {
        s -> key[0xE] = 1;
    }

    else
    {
        s -> key[0xE] = 0;
    }

    if(IsKeyPressed(KEY_Z) || IsKeyDown(KEY_Z))
    {
        s -> key[0xA] = 1;
    }

    else
    {
        s -> key[0xA] = 0;
    }

    if(IsKeyPressed(KEY_X) || IsKeyDown(KEY_X))
    {
        s -> key[0x0] = 1;
    }

    else
    {
        s -> key[0x0] = 0;
    }

    if(IsKeyPressed(KEY_C) || IsKeyDown(KEY_C))
    {
        s -> key[0xB] = 1;
    }

    else
    {
        s -> key[0xB] = 0;
    }

    if(IsKeyPressed(KEY_V) || IsKeyDown(KEY_V))
    {
        s -> key[0xF] = 1;
    }

    else
    {
        s -> key[0xF] = 0;
    }


}

void drawGraphics(Chip8* s)
{ 
    for (int y = 0; y < 32; ++y) 
    {
        for (int x = 0; x < 64; ++x) 
        {
            if (s -> display[ (y * 64) + x] != 0) 
            {
                DrawRectangle (x * 10, y * 10, 10, 10, WHITE);
            } 
            else 
            {
                DrawRectangle (x * 10, y * 10, 10, 10, BLACK);
            }
        }
	}

}

//Print Current State of the Chip
void printState(Chip8* s)
{
    printRegisters(s);
    printStack(s);
    printTimers(s);

}

void printTimers(Chip8* s)
{
    printf("Delay Timer: %X\n", s -> delay_timer);
    printf("Sound Timer: %X\n", s -> sound_timer);
    printf("\n");

}
//Print Stack
void printStack(Chip8* s)
{
    int size = 16;
    printf("STACK\n");
    for(int i = 0; i< size; i++)
    {
        printf("Stack[%X] = %X \n", i, s -> stack[i]);
    }

    printf("\n");

}
//Print Registers of Chip
void printRegisters(Chip8* s)
{
    printf("REGISTERS\n");
    int size = 0xF;
    for(int i = 0; i < size; i++)
    {
        printf("V[%X] = %X \n", i, s -> V[i]);
    }

    printf("\n");

}

//Load Program into memory
void loadProgram(Chip8* s, FILE *f, int fsize)
{

    //Read the file into memory at 0x200 and close it
    uint8_t *buffer = (uint8_t *)malloc(fsize+0x200);
    fread(buffer+0x200, fsize, 1, f);
    fclose(f);

    //Load file from buffer into chip memory
    for(int i = 0; i < fsize; i++)
    {
        s ->memory[i+0x200] = buffer[i+0x200];
    }

}

//Fetch opcode
//decode opcode
//execute opcode
void emulateCycle(Chip8* s)
{
    //Opcode
    uint16_t opcode = (s -> memory[s -> pc] << 8) | (s -> memory[(s -> pc) + 1]);
    printf("%04X\n\n", (opcode));

    //FirstByte of the Opcode
    uint16_t firstByte = opcode & 0xF000;



    //Decode opcode
    switch(firstByte)
    {
        case 0x0000:
            Op0(s, opcode);
            break;

        //Jump to NNN
        case 0x1000:
            Op1(s, opcode);
            break;
            

        case 0x2000:
            Op2(s, opcode);
            break;


        //Skip if VX == NN
        case 0x3000:
            Op3(s, opcode);
            break;


        //Skip if VX != NN
        case 0x4000:
            Op4(s, opcode);
            break;

        //Skip if VX == VY
        case 0x5000: 
            Op5(s, opcode);
            break;

            //Store NN in VX
        case 0x6000:
            Op6(s, opcode);
            break;


        //Add the value NN to register VX
        case 0x7000:
            Op7(s, opcode);
            break;


        //Set VX to VY
        case 0x8000:
            Op8(s, opcode);
            break;



        //Skip if VX != VY
        case 0x9000:
            Op9(s, opcode);
            break;

        // ANNN: Sets I to the address NNN
        case 0xA000:
            //Execute Opcode
            OpA(s, opcode);
            break;

        //PC = V0 + NNN
        case 0xB000:
            OpB(s, opcode);
            break;

        case 0xC000:
            OpC(s, opcode);
            break;

        //Draws Sprite at coordinate (VX, VY)
        case 0xD000:
            OpD(s, opcode);
            break;


        case 0xE000:
            OpE(s, opcode);
            break;

        case 0xF000:
            OpF(s, opcode);
            break;

        default:
            printf("Unknwon opcode 0x%X\n", opcode);
    }

    if(s -> delay_timer > 0)
    {
        --(s -> delay_timer);
    }

    if(s -> sound_timer > 0)
    {
        if(s -> sound_timer == 1)
        {
            printf("BEEP\n");
            --(s -> sound_timer);
        }
    }
}



