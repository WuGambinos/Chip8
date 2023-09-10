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

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "../include/emu.h"
#include "../include/raygui.h"

int main(int argc, char** argv) {
    argc = argc;
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    const int FPS = 500;
    bool main_window = true;
    bool emu_window = true;

    char debug_strings[100];

    FILE* f = fopen(argv[1], "rb");

    if (f == NULL) {
        printf("Error: Couldn't open rom\n");
        exit(1);
    }

    fseek(f, 0L, SEEK_END);
    int file_size = ftell(f);
    fseek(f, 0L, SEEK_SET);

    Chip8* chip = init_chip8();

    load_program(chip, f, file_size);

    // RAYLIB and RAYGUI
    SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Chip8 Virtual Machine");

    SetTargetFPS(FPS);

    while (!WindowShouldClose()) {
        // Update
        //----------------------------------------------------------------------------------

        BeginDrawing();

        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        // raygui: controls drawing
        //----------------------------------------------------------------------------------
        if (main_window) {
            main_window = !GuiWindowBox(
                (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}, "Main Window");
        }
        if (emu_window) {
            emu_window =
                !GuiWindowBox((Rectangle){200, 200, 432, 216}, "Screen");
        }

        emulate_cycle(chip);
        check_keys(chip);

        if (chip->drawFlag == 1) {
            draw_graphics(chip, 220, 250);
        }

        sprintf(debug_strings, "PC: 0x%X", chip->pc);
        DrawText(debug_strings, 700, 40, 10, RED);

        sprintf(debug_strings, "SP: 0x%X", chip->sp);
        DrawText(debug_strings, 700, 55, 10, RED);

        for (int i = 0; i < 0xF; i++) {
            sprintf(debug_strings, "V[%X] = 0x%X", i, chip->V[i]);
            DrawText(debug_strings, 700, 70 + (i * 10), 10, RED);
        }

        EndDrawing();
    }
    CloseWindow();

    return 0;
}
