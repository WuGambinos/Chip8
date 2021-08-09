#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "emu.h"
#include "raylib.h"



/*
int main(argc, char **argv)
{
    //Set Up Render System and register inpupt callbakcs

    //Initialize the Chip8 system and load game into memory

    //Emulation loop

    for(;;)
    {
        //Emulate one cycle

        //If draw flag set, update screen

        //Store key press state (Press and Release)
    }
}*/
int main(void) {
    printf("Hello, World!\n");
    char winPath[] = "C:/Users/lajua/Desktop/Programming/Chip8/src/roms/test_opcode.ch8";
    char macPath[] = "/Users/lajuanstation/Desktop/Chip8C/src/roms/RPS.ch8";
    char archPath[] = "/home/lajuan/Programming/Chip8C/roms/Fishie.ch8";


    FILE *f = fopen(winPath, "rb");

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
InitWindow (820, 320, "Chip8 Virtual Machine");
SetTargetFPS(60);

    while(!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground (BLUE);

        emulateCycle(chip);
        		
        // If the draw flag is set update the screen
		if (chip -> drawFlag == 1)
        { 
            drawGraphics(chip);
        }

        DrawText("Hello World", 700, 25, 15, RED);


        EndDrawing();
    }
    CloseWindow();
    




    return 0;
}
