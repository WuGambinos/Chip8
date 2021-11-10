/*
 * =====================================================================================
 *
 *       Filename:  main.c
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

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "emu.h"
#include "../include/raylib.h"


int main(int argc, char **argv) {

    
    argc = argc;
    //Store Strings for Debugging
    char string[100];

    /*
    char winPath[] = "C:/Users/lajua/Desktop/Programming/Chip8/src/roms/tombstontipp.ch8";
    char macPath[] = "/Users/lajuanstation/Desktop/Chip8C/src/roms/RPS.ch8";
    char archPath[] = "/home/lajuan/Programming/Chip8C/roms/Fishie.ch8";
    */

    //Open File
    FILE *f = fopen(argv[1], "rb");

    // Halt Program if file not found 
    if(f == NULL)
    {
        printf("Error: Couldn't open rom\n");
        exit(1);
    }

    //Get File size
    fseek(f, 0L, SEEK_END);
    int fsize = ftell(f);
    fseek(f, 0L, SEEK_SET);

    //Create Chip
    Chip8* chip = InitChip8();

    //Load Program
    loadProgram(chip, f ,fsize);

    for(int i = 0; i < 100; i++) {
        emulateCycle(chip);
    }

    for(int y = 0; y < 32; y++) {
        for(int x = 0; x < 64; x++) {
            printf("%d", chip->display[(y*64) + x]);
        }
        printf("\n");
    }



/*
    for(int i = 0; i < 60; i++)
    {
        printf("PC: %X: ", (chip -> pc));
        emulateCycle(chip);

    }

    printState(chip);

*/

/* 
    while(chip -> pc < fsize+0x200)
    {
        printf("%04X: ", (chip -> pc) - 0x200);
        emulateCycle(chip);
    }
 */



    //Disassemble

/*
    int pc = 0x200;
    //Print The Hex in the rom
    while(pc < fsize+0x200)
    {
        DisassembleChip8Op(chip -> memory, pc);
        printf("\n");
        pc += 2;
    }
*/


//RAYLIB
/*
InitWindow (820, 320, "Chip8 Virtual Machine");
SetTargetFPS(120);

    while(!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground (BLUE);

        emulateCycle(chip);
        checkKeys(chip);
        		
        // If the draw flag is set update the screen
		if (chip -> drawFlag == 1)
        { 
            drawGraphics(chip);
        }

        DrawText("Hello World", 700, 25, 15, WHITE);
        sprintf(string, "PC: %X", chip -> pc);
        DrawText(string, 700, 40, 10, WHITE);

        sprintf(string, "SP: %X", chip -> sp);
        DrawText(string, 700, 55,10, WHITE);

        for(int i = 0; i < 0xF; i++)
        {
            sprintf(string, "V[%X] = %X", i, chip -> V[i]);
            DrawText(string, 700, 70 + (i * 10), 10, WHITE);
        }


        EndDrawing();
    }
    CloseWindow();
    */




    return 0;
}