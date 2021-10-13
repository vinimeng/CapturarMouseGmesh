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


// Desenvolvido por Vinícius Meng - 0250583

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
    FILE *filePointer;
    char *nomeArquivo = "mesh.geo";

    InitWindow(screenWidth, screenHeight, "Capturar mouse");

    Vector2 ballPosition = {-100.0f, -100.0f};
    Color ballColor = BEIGE;

    int touchCounter = 0;

    int touchedCounter = 0;
    Vector2 touchedPositions[MAX_TOUCH_POINTS];

    filePointer = fopen(nomeArquivo, "w");
    fprintf(filePointer, "lc = 0.3;\n\n");

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
                fprintf(filePointer, "Point(%d) = {%f, %f, 0, lc};\n", touchedCounter + 1, touchedPositions[touchedCounter].x / 1000, touchedPositions[touchedCounter].y / 1000);
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

    fprintf(filePointer, "\n\n\n// cria linhas\n");

    int i;

    for (i = 1; i < touchedCounter; i++)
    {
        fprintf(filePointer, "Line(%d)={%d,%d};\n", i, i, i + 1);
    }

    fprintf(filePointer, "Line(%d)={%d,%d};\n", i, i, 1);

    fprintf(filePointer, "\n\n\n// cria superficie\n");

    fprintf(filePointer, "Curve Loop(1) = {");

    for (i = 1; i < touchedCounter; i++)
    {
        fprintf(filePointer, "%d,", i);
    }

    fprintf(filePointer, "%d};\n", i);

    fprintf(filePointer, "\nPlane Surface(1) = {1}; \n");

    fprintf(filePointer, "\nPhysical Surface (1) = {1};");

    fclose(filePointer);

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
