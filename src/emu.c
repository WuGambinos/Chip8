//
// Created by lajua on 8/1/2021.
//
#include "emu.h"
#include "font.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

//Initialize Chip-8
Chip8* InitChip8(void)
{
    //Create Chip
    Chip8* s  = (Chip8*) calloc(sizeof(Chip8), 1);

    s -> pc = 0x200;    //Program counter starts at 0x200
    s -> opcode = 0;    //Reset Current opcode
    s -> sp = 0;        //Reset index register
    s -> I = 0;         //Reset stack pointer

    s -> halt = 0;      //Clear Halt Flag

    s -> drawFlag = 1;   //Clear draw flag

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

void Op0(Chip8* s, uint16_t opcode)
{
    switch((opcode & 0x000F))
    {
        //0x00E0: Clears the Screen
        case 0x0000:
            //Execute Code
            for(int i = 0; i < (64 * 32); i++)
            {
                s -> display[i] = 0;
            }

            s -> drawFlag = 1;
            s -> pc += 2;
            break;

        case 0x000E: //0x00EE: Return
                (s -> sp)--;
                s -> pc = s -> stack[s -> sp];
                s -> pc += 2;
            break;

        default:
            printf("Unknown opcode [0x0000]L 0x%X\n",opcode);
    }
}

void Op1(Chip8 *s, uint16_t opcode)
{
    if((opcode & 0x0FFF) == s -> pc)
        {
            s -> halt = 1;
            printf("INFINITE LOOP\n");
            //exit(1);
        }

        s -> pc = opcode & 0x0FFF;

}

void Op2(Chip8 *s, uint16_t opcode)
{
        s -> stack[s -> sp] = s -> pc;
        (s -> sp)++;
        s -> pc = opcode & 0x0FFF;
}

void Op3(Chip8 *s, uint16_t opcode)
{
        uint8_t x = (opcode & 0x0F00) >> 8;
        if(s -> V[x] == (opcode & 0x00FF))
        {
            s -> pc += 4;
        } else
        {
            s -> pc += 2;
        }

}

void Op4(Chip8 *s, uint16_t opcode)
{
        uint8_t x = (opcode & 0x0F00) >> 8;
        if(s -> V[x] != (opcode & 0x00FF))
        {
            s -> pc += 4;
        } else
        {
            s -> pc += 2;
        }

}

void Op5(Chip8 *s, uint16_t opcode)
{
        uint8_t x = (opcode & 0x0F00) >> 8;
        uint8_t y = (opcode & 0x00F0) >> 4;

        
        if(s -> V[x] == s -> V[y])
        {
            s -> pc += 4;
        }

        else
        {
            s -> pc += 2;
        }
}

void Op6(Chip8 *s, uint16_t opcode)
{
        uint8_t x = (opcode & 0x0F00) >> 8;;
        s -> V[x] = opcode & 0x00FF;
        s -> pc += 2;
}

void Op7(Chip8 *s, uint16_t opcode)
{
        uint8_t x = (opcode & 0x0F00) >> 8;
        s -> V[x] += opcode & 0x00FF;
        s -> pc += 2;
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


            switch(opcode & 0x000F)
            {

                case 0x0000:
                {
                    uint8_t x = (opcode & 0x0F00) >> 8;
                    uint8_t y = (opcode & 0x00F0) >> 4;
                    s -> V[x] = s -> V[y];
                    s -> pc += 2;
                }
                break;

                //VX = VX | VY
                case 0x0001:
                {
                    uint8_t x = (opcode & 0x0F00) >> 8;
                    uint8_t y = (opcode & 0x00F0) >> 4;
                    s -> V[x] |= s -> V[y];
                    s -> pc += 2;
                }
                break;

                //VX = VX & VY
                case 0x0002:
                {
                    uint8_t x = (opcode & 0x0F00) >> 8;
                    uint8_t y = (opcode & 0x00F0) >> 4;
                    s -> V[x] &= s -> V[y];
                    s -> pc += 2;
                }
                break;

                // VX = VX ^ VY;
                case 0x0003:
                {
                    uint8_t x = (opcode & 0x0F00) >> 8;
                    uint8_t y = (opcode & 0x00F0) >> 4;
                    s -> V[x] ^= s -> V[y];
                    s -> pc += 2;
                }
                break;

                //Add
                case 0x0004:
                {
                    uint8_t x = (opcode & 0x0F00) >> 8;
                    uint8_t y = (opcode & 0x00F0) >> 4;

                    //Check if y > 255 - x
                    if(s -> V[y] > (0xFF - s -> V[x]))
                    {
                        //Set carry
                        s -> V[0xF] = 1;
                    }
                    else
                    {
                        //Clear Carry
                        s -> V[0xF] = 0;
                    }
                    //V[x] += V[y]
                    s -> V[x] += s -> V[y];
                    s -> pc += 2;
                }
                break;

                //Sub
                case 0x0005:
                {
                    uint8_t x = (opcode & 0x0F00) >> 8;
                    uint8_t y = (opcode & 0x00F0) >> 4;
                    //Check if y > x
                    if(s -> V[y] > ( s -> V[x]))
                    {
                        //Set Borrow
                        s -> V[0xF] = 1;
                    }

                    else
                    {
                        s -> V[0xF] = 0;
                    }
                    //V[x] -= V[y]
                    s -> V[x] -= s -> V[y];
                    s -> pc += 2;
                }
                break;

                //Right Shift
                case 0x0006:
                {
                    uint8_t x = (opcode & 0x0F00) >> 8;
                    uint8_t y = (opcode & 0x00F0) >> 4;
                    s -> V[x] = s -> V[y] >> 1;
                    s -> pc += 2;
                }
                break;

                //VX = VY - VX
                case 0x0007:
                {
                    uint8_t x = (opcode & 0x0F00) >> 8;
                    uint8_t y = (opcode & 0x00F0) >> 4;

                    //if x > y


                    if(s -> V[x] > ( s -> V[y]))
                    {
                        //Set Borrow
                        s -> V[0xF] = 1;
                    }

                    else
                    {
                        s -> V[0xF] = 0;
                    }
                    //V[x] -= V[y]
                    s -> V[x] = (s -> V[y] - s -> V[x]);
                    s -> pc += 2;


                }
                break;

                //Left Shift
                case 0x000E:
                {
                    uint8_t x = (opcode & 0x0F00) >> 8;
                    uint8_t y = (opcode & 0x00F0) >> 4;
                    s -> V[x] = s -> V[y] << 1;
                    s -> pc += 2;

                }
                break;
            }
            break;

        //Skip if VX != VY
        case 0x9000:
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            uint8_t y = (opcode & 0x00F0) >> 4;
            if(s -> V[x] != s -> V[y])
            {
                s -> pc += 4;
            }

            else
            {
                s -> pc += 2;
            }
        }
            break;

        // ANNN: Sets I to the address NNN
        case 0xA000:
            //Execute Opcode
            s -> I = opcode & 0x0FFF;
            s -> pc += 2;
            break;

        //PC = V0 + NNN
        case 0xB000:
        {
            s -> pc = (s -> V[0]) + (opcode & 0x0FFF);

        }
            break;

        case 0xC000:
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            s -> V[x] = rand() & (opcode  & 0x00FF);

            s -> pc += 2;
        }
            break;

        //Draws Sprite at coordinate (VX, VY)
        case 0xD000:
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            uint8_t y = (opcode & 0x00F0) >> 4;

            //Height
            uint8_t h = (opcode & 0x000F);

            uint8_t pixel = 0;

            s -> V[0xF] = 0;
            for(int yline = 0; yline < h; yline++)
            {
                pixel = s -> memory[(s -> I) + yline];
                for(int xline = 0; xline < 8; xline++)
                {
                    if((pixel & (0x80 >> xline)) != 0)
                    {
                       if (s -> display[( s -> V[x] + xline + ((s -> V[y] + yline) * 64))] == 1)
                       {
                           s -> V[0xF] = 1;
                       }
                       s -> display[(s -> V[x] + xline + ((s -> V[y] + yline) * 64))] ^= 1;

                    }
                }
            }

            s -> drawFlag = 1;
            s -> pc += 2;


        }
            break;


        case 0xE000:
            switch(opcode & 0x00FF)
            {
                //Skip following instruction if the key corresponding to hex value
                //currently stored in register VX is pressed
                case 0x009E:
                {
                    uint8_t x = (opcode & 0x0F00) >> 8;
                    if(s -> key[ s -> V[x]] != 0)
                    {
                        s -> pc += 4;
                    }

                    else
                    {
                        s -> pc += 2;
                    }
                }
                    break;

                //Skip following instruction if the key corresponding to hex value
                //currently stored in register VX is not pressed
                case 0x00A1:
                {
                    uint8_t x = (opcode & 0x0F00) >> 8;

                    if(s -> key[ s -> V[x]] == 0)
                    {
                        s -> pc += 4;
                    }

                    else
                    {
                        s -> pc += 2;
                    }
                }
                    break;
            }
            break;

        case 0xF000:
        {
            switch(opcode & 0x00FF)
            {
                //Set VX = delay timer value.
                case 0x0007:
                {
                    uint8_t x = (opcode & 0x0F00) >> 8;
                    s -> V[x] = s -> delay_timer;

                    s -> pc += 2;
                }
                    break;

                //Wait for a key press, store the value of the key in Vx.
                case 0x000A: {
                    int keyPress = 0;
                    uint8_t x = (opcode & 0x0F00) >> 8;
                    for (int i = 0; i < 16; i++)
                    {
                        if( s -> key[i] != 0)
                        {
                            s -> V[x] = i;
                            keyPress = 1;
                        }
                    }
                    //If no keypress skip cycle and try again
                    if(!keyPress)
                    {
                        return;
                    }
                    s -> pc += 2;
                }break;


                //delay_timer = VX
                case 0x0015:
                {
                    uint8_t x = (opcode & 0x0F00) >> 8;
                    s -> delay_timer = s -> V[x];

                    s -> pc += 2;
                }
                    break;

                //sound_timer = VX
                case 0x0018:
                {
                    uint8_t x = (opcode & 0x0F00) >> 8;
                    s -> sound_timer = s -> V[x];

                    s -> pc += 2;

                }
                    break;
                //I += VX
                case 0x001E:
                {
                    uint8_t x = (opcode & 0x0F00) >> 8;
                    s -> I += s -> V[x];

                    s -> pc += 2;
                }
                    break;


                case 0x0029:

                    s -> pc += 2;
                    break;

                //Store BCD representation of VX in memory locations I, I+1, and I+2.
                case 0x0033: {
                    uint8_t x = (opcode & 0x0F00) >> 8;

                    //Hundreds Digit
                    s -> memory[s -> I] = ((s -> V[x]) / 100) % 10;

                    //Tens Digit
                    s -> memory[(s -> I) + 1] = ((s -> V[x]) /10) % 10;

                    //Ones Digit
                    s -> memory[(s -> I) + 2] = (s -> V[x]) % 10;

                    s -> pc += 2;
                }

                    break;

                //Store registers V0 through VX in memory starting at location I.
                case 0x0055:
                {
                    uint8_t i = 0x00;
                    uint8_t x = (opcode & 0x0F00) >> 8;
                    while(i <= x)
                    {
                        s -> memory[(s -> I) + i] = s -> V[i];
                        i++;
                    }

                    s -> pc += 2;

                }
                    break;

                //Read registers V0 through Vx from memory starting at location I.
                case 0x0065:
                {
                    uint8_t i = 0x00;
                    uint8_t x = (opcode & 0x0F00) >> 8;

                    while(i <= x)
                    {
                        s -> V[i] = s -> memory[(s -> I) + i];
                        i++;
                    }

                    s -> pc += 2;

                }
                    break;

            }
        }


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



