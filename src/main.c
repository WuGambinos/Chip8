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
    bool main_window_open = true;
    bool emu_window_open = true;
    bool debug_window_open = true;

    Rectangle main_window = (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    Rectangle emu_window = (Rectangle){200, 200, 432, 216};
    Rectangle debug_window = (Rectangle){700, 20, 100, 300};

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

    GuiLoadStyle("styles/dark.rgs");

    SetTargetFPS(FPS);

    while (!WindowShouldClose()) {
        // Update
        //----------------------------------------------------------------------------------

        BeginDrawing();

        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        // raygui: controls drawing
        //----------------------------------------------------------------------------------
        if (main_window_open) {
            main_window_open = !GuiWindowBox(main_window, "Main Window");
        }
        if (emu_window_open) {
            emu_window_open = !GuiWindowBox(emu_window, "Screen");
        }

        if (debug_window_open) {
            debug_window_open = !GuiWindowBox(debug_window, "Debug");
        }

        emulate_cycle(chip);
        check_keys(chip);

        if (chip->drawFlag == 1) {
            draw_graphics(chip, 220, 250);
        }

        sprintf(debug_strings, "PC: 0x%X", chip->pc);
        DrawText(debug_strings, 700, 50, 10, WHITE);

        sprintf(debug_strings, "SP: 0x%X", chip->sp);
        DrawText(debug_strings, 700, 65, 10, WHITE);

        for (int i = 0; i < 0xF; i++) {
            sprintf(debug_strings, "V[%X] = 0x%X", i, chip->V[i]);
            DrawText(debug_strings, 700, 90 + (i * 10), 10, WHITE);
        }

        EndDrawing();
    }
    CloseWindow();

    return 0;
}
