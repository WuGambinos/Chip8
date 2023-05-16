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
#include "../include/emu.h"
#include "../include/raylib.h"

#define SCREEN_WIDTH 840
#define SCREEN_HEIGHT 320 
#define FPS 500

int main(int argc, char **argv) {
    
    argc = argc;
    //Store Strings for Debugging
    char string[100];

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

    //RAYLIB
    InitWindow (SCREEN_WIDTH, SCREEN_HEIGHT, "Chip8 Virtual Machine");
    SetTargetFPS(FPS);

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

        sprintf(string, "PC: 0x%X", chip -> pc);
        DrawText(string, 700, 40, 10, WHITE);

        sprintf(string, "SP: 0x%X", chip -> sp);
        DrawText(string, 700, 55,10, WHITE);

        for(int i = 0; i < 0xF; i++)
        {
            sprintf(string, "V[%X] = 0x%X", i, chip -> V[i]);
            DrawText(string, 700, 70 + (i * 10), 10, WHITE);
        }


        EndDrawing();
    }
    CloseWindow();

    return 0;
}
