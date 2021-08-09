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

void DisassembleChip8Op(uint8_t *codebuffer, int pc)
{
    //Pointer to bytes, All CHIP-8 instructions are 2 bytes each
    uint8_t *code = &codebuffer[pc];

    //Get First Nibble, EX. 00 e0.  It grabs the 00 part
    uint8_t firstnib = (code[0]  >> 4);

    //Prints Program counter followed by hex code
    printf("%04x %02x %02x ", pc, code[0], code[1]);


    //prints instruction for first nibble
    switch (firstnib)
    {
        case 0x0:
            switch(code[1])
            {

                case 0xe0:
                    printf("%-10s", "CLS");
                    break;

                case 0xee:
                    printf("%-10s", "RTS");
                    break;

                default:
                    printf("UNKNOWN 0");
                    break;

            }

            break;


        case 0x01:
        {

            printf("%-10s $%01x%02x\n", "JMP", code[0] & 0xf, code[1]);
        }
            break;

        case 0x02:
            printf("%-10s $%01x%02x", "CALL", code[0] & 0xf, code[1]);
            break;

        case 0x03:
            printf("%-10s V%01X, #$%02X", "SKIP.EQ", code[0] & 0xf, code[1]);
            break;

        case 0x04:
            printf("%-10s V%01X, #$%02X", "SKIP.NOTEQ", code[0] & 0xf, code[1]);
            break;

        case 0x05:
            printf("%-10s V%01X, V%01X", "SKIP.EQ", code[0] & 0xf, code[1] >> 4);
            break;

        case 0x6:
            printf("%-10s V%01X,#$%02x", "MVI", code[0]&0xf, code[1]);
            break;

        case 0x07:
            printf("%-10s V%01X, #$%02X", "ADD", code[0] & 0xf, code[1]);
            break;

        case 0x08:
        {
            uint8_t lastnibble = code[1] & 0xf;
            switch(lastnibble)
            {

                case 0:
                    printf("%-10s V%01X, V%01X", "MOV", code[0] & 0xf, code[1] >> 4);
                    break;

                case 1:
                    printf("%-10s V%01X, V%01X", "OR", code[0] & 0xf, code[1] >> 4);
                    break;

                case 2:
                    printf("%-10s V%01X, V%01X", "AND", code[0] & 0xf, code[1] >> 4);
                    break;

                case 3:
                    printf("%-10s V%01X, V%01X", "XOR", code[0] & 0xf, code[1] >> 4);
                    break;

                case 4:
                    printf("%-10s V%01X, V%01X", "ADC", code[0] & 0xf, code[1] >> 4);
                    break;

                case 5:
                    printf("%-10s V%01X, V%01X, V%01X", "SUBC", code[0] & 0xf, code[0] & 0xf, code[1] >> 4);
                    break;

                case 6:
                    printf("%-10s V%01X, V%01X", "SHR", code[0] & 0xf, code[1] >> 4);
                    break;

                case 7:
                    printf("%-10s V%01X, V%01X, V%01X", "SUB", code[0] & 0xf, code[1] >> 4, code[1] >> 4);
                    break;

                case 0x0e:
                    printf("%-10s V%01X, V%01X" , "SHL", code[0] & 0xf, code[1] >> 4);
                    break;

            }

        }

            break;

        case 0x09:
            printf("%-10s V%01X, V%01X", "SKIP.NE", code[0] & 0xf, code[1] >> 4);
            break;


        case 0x0a:

            printf("%-10s I, #$%01x%02x", "MVI", code[0] & 0xf, code[1]);
            break;


        case 0x0b:
        {

            printf("%-10s JMP #$%01x%02x", code[0] & 0xf, code[1]);

        }
            break;

        case 0x0c:
            printf("%-10s V%01X, V%02X", "RAND MASK", code[0] & 0xf, code[1]);
            break;

        case 0x0d:
            printf("%-10s V%01X, V%01X, #$%01X", "DISP", code[0] & 0xf, code[1] >> 4, code[1] & 0xf);
            break;

        case 0x0e:
        {

            switch(code[1])
            {
                case 0x9e:
                    printf("%-10s V%01X", "SKIPKEY.Y", code[0] & 0xf);
                    break;

                case 0xa1:
                    printf("%-10s V%01X", "SKIPKEY.N", code[0] & 0xf);
                    break;

                default:
                    printf("UNKNOWN E");
                    break;
            }

        }
            break;

        case 0x0f:
            switch(code[1])
            {
                case 0x07:
                    printf("%-10s V%01X, DELAY", "MOV", code[0] & 0xf);
                    break;

                case 0x0a:
                    printf("%-10s V%01X", "KEY", code[0] & 0xf);
                    break;

                case 0x15:
                    printf("%-10 DELAY, V%01X", "MOV", code[0] & 0xf);
                    break;

                case 0x18:
                    printf("%-10 SOUND, V%01X", "MOV", code[0] & 0xf);
                    break;

                case 0x1e:
                    printf("%-10s I, V%01X", "ADI", code[0] & 0xf);
                    break;

                case 0x29:
                    printf("%-10s I, V%01X", "SPRITECHAR", code[0] & 0xf);
                    break;

                case 0x33:
                    printf("%-10s (I), V%01X", "MOVBCD", code[0] & 0xf);
                    break;

                case 0x55:
                    printf("%-10s (I), V0-V%01X", "MOVM", code[0] & 0xf);
                    break;

                case 0x65:
                    printf("%-10s V0-V%01X, (I)", "MOVM", code[0] & 0xf);
                    break;

                default:
                    printf("UNKNOWN F");
                    break;
            }
            break;

    }
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
            s -> pc += 2;
            break;

        case 0x000E: //0x00EE: Return
            s -> sp += 2;
            s -> pc += (s -> memory[s -> sp] << 8) | s-> memory[s -> sp + 1];
            break;

        default:
            printf("Unknown opcode [0x0000]L 0x%X\n",opcode);
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
            //Get Last 4 bits Ex. 00EE, grabs the far Right Digit
            switch(opcode & 0x000F)
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
                    /*
                    s -> sp += 2;
                    s -> pc += (s -> memory[s -> sp] << 8) | s-> memory[s -> sp + 1];
                    */
                    (s -> sp)--;
                    s -> pc = s -> stack[s -> sp];
                    s -> pc += 2;
                    break;

                    default:
                        printf("Unknown opcode [0x0000]L 0x%X\n",opcode);
            }
            break;

        //Jump to NNN
        case 0x1000:

            if((opcode & 0x0FFF) == s -> pc)
            {
                s -> halt = 1;
                printf("INFINITE LOOP\n");
                //exit(1);
            }

            s -> pc = opcode & 0x0FFF;
            break;

        case 0x2000:
            s -> stack[s -> sp] = s -> pc;
            (s -> sp)++;
            s -> pc = opcode & 0x0FFF;
            break;

        //Skip if VX == NN
        case 0x3000:
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
        break;

        //Skip if VX != NN
        case 0x4000:
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
        break;

        //Skip if VX == VY
        case 0x5000: {
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
        break;

            //Store NN in VX
            case 0x6000:
            {
                uint8_t x = (opcode & 0x0F00) >> 8;;
                s -> V[x] = opcode & 0x00FF;
                s -> pc += 2;
            };
        break;

        //Add the value NN to register VX
        case 0x7000:
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            s -> V[x] += opcode & 0x00FF;
            s -> pc += 2;
        }
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



