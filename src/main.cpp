#include "raylib.h"
#include "raymath.h"

#include "AnimationData.h"
#include "Character.h"

int main()
{
    // [width, height]
    int windowDimensions[]{800, 600};
    // Window dimension
    InitWindow(windowDimensions[0], windowDimensions[1], "Raylib Classy Clash");

    Texture2D mapTexture{LoadTexture("map/map0.png")};
    Vector2 mapPosition{}; // Will be initialzed to {0.0f, 0.0f}
    const float mapScale{4.0f};

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

    knight.updateScreenPosition(windowDimensions[0], windowDimensions[1]);

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

        // undo the knight movement when out of bound
        const Vector2 currentKnightWorldPosition = knight.getWorldPosition();
        if (currentKnightWorldPosition.x < 0.0f ||
            currentKnightWorldPosition.x > mapTexture.width * mapScale - windowDimensions[0] ||
            currentKnightWorldPosition.y < 0.0f ||
            currentKnightWorldPosition.y > mapTexture.height * mapScale - windowDimensions[1])
        {
            knight.undoMovement();
        }

        EndDrawing();
    }

    /// Clean ups
    UnloadTexture(mapTexture);

    CloseWindow();
}
