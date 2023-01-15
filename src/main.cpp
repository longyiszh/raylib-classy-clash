#include "raylib.h"
#include "raymath.h"

#include "AnimationData.h"
#include "Character.h"

int main()
{
    // Window dimension
    const int windowWidth{800};
    const int windowHeight{600};
    InitWindow(windowWidth, windowHeight, "Raylib Classy Clash");

    Texture2D mapTexture{LoadTexture("map/map0.png")};
    Vector2 mapPosition{}; // Will be initialzed to {0.0f, 0.0f}

    Character knight(
        // Textures here must have same width and height
        LoadTexture("assets/characters/knight_idle_spritesheet.png"),
        LoadTexture("assets/characters/knight_run_spritesheet.png"),
        8.0f);

    Texture2D knightCurrentTexture = knight.getCurrentTexture();
    float knightTextureRangeWidth = knightCurrentTexture.width / 6.0f;
    float knightTextureRangeHeight = knightCurrentTexture.height;

    AnimationData knightAnimData(
        6,
        1,
        knightTextureRangeWidth,
        knightTextureRangeHeight,
        1.0 / 12.0);

    knight.setAnimData(
        &knightAnimData);

    knight.updateScreenPosition(windowWidth, windowHeight);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // time since last frame
        float deltaTime{GetFrameTime()};

        BeginDrawing();
        ClearBackground(WHITE);

        /**
         * Instead of moving character on the map,
         * We fix charcter in the middle of the window
         * And move map
         */
        mapPosition = Vector2Negate(knight.getWorldPosition());

        // draw map
        DrawTextureEx(
            mapTexture,
            mapPosition,
            0.0f,
            4.0f,
            WHITE);

        // update knight postion, anims and draw it
        knight.tick(deltaTime);

        EndDrawing();
    }

    /// Clean ups
    UnloadTexture(mapTexture);

    CloseWindow();
}
