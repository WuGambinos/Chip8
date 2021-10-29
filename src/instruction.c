
#include "instruction.h"

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

        //0x00EE: Return
        case 0x000E: 
                (s -> sp)--;
                s -> pc = s -> stack[s -> sp];
                s -> pc += 2;
            break;

        default:
            printf("Unknown opcode [0x0000]L 0x%X\n",opcode);
    }
}

//1NNN - JMP NNN
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

//2NNN - Call NNN
void Op2(Chip8 *s, uint16_t opcode)
{
        s -> stack[s -> sp] = s -> pc;
        (s -> sp)++;
        s -> pc = opcode & 0x0FFF;
}

//3XKK - Skip if VX == KK
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

//4XKK - Skip if VX != KK
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

//5XY0 - Skip if VX == VY
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

//6XKK - Set VX = KK
void Op6(Chip8 *s, uint16_t opcode)
{
        uint8_t x = (opcode & 0x0F00) >> 8;;
        s -> V[x] = opcode & 0x00FF;
        s -> pc += 2;
}

//7XKK - VX += KK
void Op7(Chip8 *s, uint16_t opcode)
{
        uint8_t x = (opcode & 0x0F00) >> 8;
        s -> V[x] += opcode & 0x00FF;
        s -> pc += 2;
}


void Op8(Chip8 *s, uint16_t opcode)
{

    switch(opcode & 0x000F)
    {
        //8XY0 - Set VX = VY
        case 0x0000:
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            uint8_t y = (opcode & 0x00F0) >> 4;
            s -> V[x] = s -> V[y];
            s -> pc += 2;
        }
        break;

        //8XY1 - VX = VX | VY
        case 0x0001:
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            uint8_t y = (opcode & 0x00F0) >> 4;
            s -> V[x] |= s -> V[y];
            s -> pc += 2;
        }
        break;

        //8XY2 - VX = VX & VY
        case 0x0002:
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            uint8_t y = (opcode & 0x00F0) >> 4;
            s -> V[x] &= s -> V[y];
            s -> pc += 2;
        }
        break;

        //8XY3 -  VX = VX ^ VY;
        case 0x0003:
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            uint8_t y = (opcode & 0x00F0) >> 4;
            s -> V[x] ^= s -> V[y];
            s -> pc += 2;
        }
        break;

        //8XY4 - Set VX = VX + VY, set  VF = carry 
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

        //8XY5 - Set VX = VX - VY, set VF = NOT borrow
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

        //8XY6 - Set VX = VX >> 1
        case 0x0006:
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            uint8_t y = (opcode & 0x00F0) >> 4;

            s -> V[0xF] = s -> V[x] & 1;
            s -> V[x] = s -> V[y] >> 1;
            
            s -> pc += 2;
        }
        break;

        //8XY7 - Set VX = VY - VX, set VF = NOT borrow
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

        //8XYE - Set VX = VX << 1
        case 0x000E:
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            uint8_t y = (opcode & 0x00F0) >> 4;

            s -> V[0xF] = s -> V[x] & 0x80;
            s -> V[x] = s -> V[y] << 1;
            s -> pc += 2;

        }
        break;
    }
}

//9XY0 - Skip if VX != VY
void Op9(Chip8 *s, uint16_t opcode)
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

//ANNN - Set I = NNN
void OpA(Chip8 *s, uint16_t opcode)
{
            //Execute Opcode
        s -> I = opcode & 0x0FFF;
        s -> pc += 2;
}

//BNNN - JMP to NNN + V0
void OpB(Chip8 *s, uint16_t opcode)
{
    s -> pc = (s -> V[0]) + (opcode & 0x0FFF);
}

//CXKK - Set VX = (random byte) & (KK)
void OpC(Chip8 *s, uint16_t opcode)
{
    uint8_t x = (opcode & 0x0F00) >> 8;
    s -> V[x] = rand() & (opcode  & 0x00FF);

    s -> pc += 2;
}


//DXYN - Display n-byte sprite starting at memory location I at (VX, VY), set VF = collision
void OpD(Chip8 *s, uint16_t opcode)
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


void OpE(Chip8 *s, uint16_t opcode)
{
    switch(opcode & 0x00FF)
    {
        //EX9E
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

        //EXA1
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

}

void OpF(Chip8 *s, uint16_t opcode)
{
    switch(opcode & 0x00FF)
    {
        //FX07
        //Set VX = delay timer value.
        case 0x0007:
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            s -> V[x] = s -> delay_timer;

            s -> pc += 2;
        }
            break;

        //FX0A
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


        //FX15
        //delay_timer = VX
        case 0x0015:
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            s -> delay_timer = s -> V[x];

            s -> pc += 2;
        }
            break;

        //FX18
        //sound_timer = VX
        case 0x0018:
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            s -> sound_timer = s -> V[x];

            s -> pc += 2;

        }
            break;

        //FX1E
        //I += VX
        case 0x001E:
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            s -> I += s -> V[x];

            s -> pc += 2;
        }
            break;


        //FX29
        //Set I = location of sprite for digit VX
        case 0x0029:
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
        
            s -> I = s -> V[x] * 5;
            s -> pc += 2;
        }
            break;

        //FX33
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

        //FX55
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

        //FX65
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