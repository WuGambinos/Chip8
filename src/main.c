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

int main(int argc, char **argv) {

  argc = argc;
  const int screenWidth = 800;
  const int screenHeight = 600;
  bool mainWindow = true;
  bool emuWindow = true;
  const int fps = 500;

  // Store Strings for Debugging
  char string[100];

  // Open File
  FILE *f = fopen(argv[1], "rb");

  // Halt Program if file not found
  if (f == NULL) {
    printf("Error: Couldn't open rom\n");
    exit(1);
  }

  // Get File size
  fseek(f, 0L, SEEK_END);
  int fsize = ftell(f);
  fseek(f, 0L, SEEK_SET);

  // Create Chip
  Chip8 *chip = InitChip8();

  // Load Program
  loadProgram(chip, f, fsize);

  // RAYLIB and RAYGUI
  SetConfigFlags(FLAG_WINDOW_UNDECORATED);
  InitWindow(screenWidth, screenHeight, "Chip8 Virtual Machine");

  SetTargetFPS(fps);

  while (!WindowShouldClose()) {

    // Update
    //----------------------------------------------------------------------------------

    BeginDrawing();

    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

    // raygui: controls drawing
    //----------------------------------------------------------------------------------
    if (mainWindow) {
      mainWindow = !GuiWindowBox((Rectangle){0, 0, 800, 600}, "Main Window");
    }
    if (emuWindow) {
      emuWindow = !GuiWindowBox((Rectangle){200, 200, 432, 216}, "Screen");
    }

    emulateCycle(chip);
    checkKeys(chip);

    // If the draw flag is set update the screen
    if (chip->drawFlag == 1) {
      drawGraphics(chip, 220, 250);
    }

   sprintf(string, "PC: 0x%X", chip->pc);
   DrawText(string, 700, 40, 10, RED);

   sprintf(string, "SP: 0x%X", chip->sp);
   DrawText(string, 700, 55, 10, RED);

   for (int i = 0; i < 0xF; i++) {
     sprintf(string, "V[%X] = 0x%X", i, chip->V[i]);
     DrawText(string, 700, 70 + (i * 10), 10, RED);
   }

    EndDrawing();
  }
  CloseWindow();

  return 0;
}
