#include "raylib.h"

int main()
{
    // Window dimension
    const int windowWidth = 800;
    const int windowHeight = 600;
    InitWindow(windowWidth, windowHeight, "Raylib Classy Clash");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        DrawText("Raylib works!", 200, 200, 60, GREEN);

        EndDrawing();
    }
    CloseWindow();
}