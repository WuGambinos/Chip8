/*
 * =====================================================================================
 *
 *       Filename:  disassemble.c
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

/* Function: DisassembleChip80p
 * ---------------------------
 * Disassembles a byte of opcode for the Chip8 sysetm
 *
 * codebuffer: buffer where opcode is stored
 * pc: program counter
 *
 *
 *
 */

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