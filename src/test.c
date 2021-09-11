

/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "../include/raylib.h"
#include <stdio.h>
#include "emu.h"


int main()
{
    bool isInMenu = true;
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update here
        if(isInMenu)
        {
            if(IsKeyPressed(KEY_Q)) isInMenu = false;
        }
        else
        {
            if(IsKeyPressed(KEY_W)) isInMenu = true;
        }

        // Draw here
        BeginDrawing();
        if(isInMenu)
        {
            ClearBackground(RAYWHITE);
            DrawText("This is the menu", 190, 200, 50, LIGHTGRAY);
        }
        else
        {
            ClearBackground(RAYWHITE);
            DrawText("Congrats! You created your firstwindow!", 190, 200, 50, LIGHTGRAY);
        }
        
        EndDrawing();

    }
    //-------
}