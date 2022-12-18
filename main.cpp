#include "raylib.h"
#include "raymath.h"

/**
 * Instead of moving character on the map,
 * We fix charcter in the middle of the window
 * And move map
 */
void moveMap(Vector2 &mapPosition)
{
    float moveSpeed{8.0f};
    Vector2 direction{};
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0f;
    if (IsKeyDown(KEY_D))
        direction.x += 1.0f;
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0f;
    if (IsKeyDown(KEY_S))
        direction.y += 1.0f;

    if (Vector2Length(direction) != 0.0)
    {
        // Substract by normalized direction because
        // 1. moving map in the negative direction
        // 2. make the length to be 1
        //    otherwise we would move faster in diagonal directions (sqrt(2))
        mapPosition = Vector2Subtract(mapPosition,
                                      Vector2Scale(
                                          Vector2Normalize(direction),
                                          moveSpeed));
    }
}

int main()
{
    // Window dimension
    const int windowWidth{800};
    const int windowHeight{600};
    InitWindow(windowWidth, windowHeight, "Raylib Classy Clash");

    Texture2D mapTexture{LoadTexture("map/map0.png")};
    Vector2 mapPosition{}; // Will be initialzed to {0.0f, 0.0f}

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        moveMap(mapPosition);

        // draw map
        DrawTextureEx(
            mapTexture,
            mapPosition,
            0.0f,
            4.0f,
            WHITE);

        EndDrawing();
    }

    /// Clean ups
    UnloadTexture(mapTexture);

    CloseWindow();
}
