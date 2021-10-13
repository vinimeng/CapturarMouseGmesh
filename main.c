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

#include <stdio.h>
#include "raylib.h"

#define MAX_TOUCH_POINTS 100

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1024;
    const int screenHeight = 600;
    char mousePosition[100];
    int mouseX = 0;
    int mouseY = 0;

    InitWindow(screenWidth, screenHeight, "Capturar mouse");

    Vector2 ballPosition = {-100.0f, -100.0f};
    Color ballColor = BEIGE;

    int touchCounter = 0;

    int touchedCounter = 0;
    Vector2 touchedPositions[MAX_TOUCH_POINTS];

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        mouseX = GetMouseX();
        mouseY = GetMouseY();

        snprintf(mousePosition, 100, "MouseX: %d / MouseY: %d", mouseX, mouseY);

        ballPosition = GetMousePosition();

        ballColor = BEIGE;

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            ballColor = MAROON;

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            touchedPositions[touchedCounter] = GetTouchPosition(0);
            if ((touchedPositions[touchedCounter].x >= 0) && (touchedPositions[touchedCounter].y >= 0)) // Make sure point is not (-1,-1) as this means there is no touch for it
            {
                touchedCounter++;
            }
            touchCounter = 10;
        }

        if (touchCounter > 0)
            touchCounter--;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Clique dentro da janela para capturar as coordenadas do seu mouse!", 150, 300, 20, DARKGRAY);

        DrawText(mousePosition, 600, 400, 20, GRAY);

        // Draw the normal mouse location
        DrawCircleV(ballPosition, 10 + (touchCounter * 3.0f), ballColor);

        for (int i = 0; i < touchedCounter; ++i)
        {
            // Draw circle and touch index number
            DrawCircleV(touchedPositions[i], 15, ORANGE);
            DrawText(TextFormat("%d", i), (int)touchedPositions[i].x - 10, (int)touchedPositions[i].y - 40, 22, BLACK);
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
