#include <raylib.h>
#include <raymath.h>

#include "AnimationData.h"
#include "Character.h"
#include "Enemy.h"
#include "Prop.h"

int main()
{
    // [width, height]
    int windowDimensions[]{800, 600};
    // Window dimension
    InitWindow(windowDimensions[0], windowDimensions[1], "Raylib Classy Clash");

    Texture2D mapTexture{LoadTexture("map/map0.png")};
    Vector2 mapPosition{}; // Will be initialzed to {0.0f, 0.0f}
    const float mapScale{4.0f};

    // knight
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

    // An Enemy
    Enemy aGoblin(
        // Textures here must have same width and height
        LoadTexture("assets/characters/goblin_idle_spritesheet.png"),
        LoadTexture("assets/characters/goblin_run_spritesheet.png"),
        3.0f);

    Texture2D aGoblinCurrentTexture = aGoblin.getCurrentTexture();
    float aGoblinTextureRangeWidth = aGoblinCurrentTexture.width / 6.0f;
    float aGoblinTextureRangeHeight = aGoblinCurrentTexture.height;

    AnimationData aGoblinAnimData(
        6,
        1,
        aGoblinTextureRangeWidth,
        aGoblinTextureRangeHeight,
        1.0 / 12.0);

    aGoblin.setAnimData(
        &aGoblinAnimData);

    aGoblin.setTarget(knight);

    // Decos
    Prop decos[]{
        Prop(Vector2{.x = 515.0f, .y = 517.0f}, LoadTexture("assets/nature_tileset/Rock.png")),
        Prop(Vector2{.x = 615.0f, .y = 717.0f}, LoadTexture("assets/nature_tileset/Log.png")),
        Prop(Vector2{.x = 815.0f, .y = 1017.0f}, LoadTexture("assets/nature_tileset/Rock.png")),
        Prop(Vector2{.x = 1015.0f, .y = 917.0f}, LoadTexture("assets/nature_tileset/Log.png")),
        Prop(Vector2{.x = 737.0f, .y = 934.0f}, LoadTexture("assets/nature_tileset/Rock.png"))};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // time since last frame
        float deltaTime{GetFrameTime()};

        BeginDrawing();
        ClearBackground(WHITE);

        // update knight postion
        knight.tick(deltaTime);

        // update goblin screen pos
        aGoblin.tick(deltaTime);

        const Vector2 &currentKnightWorldPosition = knight.getWorldPosition();

        /**
         * Instead of moving character on the map,
         * We fix charcter in the middle of the window
         * And move map
         */
        mapPosition = Vector2Negate(currentKnightWorldPosition);

        // draw map
        DrawTextureEx(
            mapTexture,
            mapPosition,
            0.0f,
            4.0f,
            WHITE);

        // draw knight
        knight.render();

        // draw aGoblin
        aGoblin.render();

        // draw decos
        for (auto &deco : decos)
        {
            deco.updateScreenPosition(currentKnightWorldPosition);
            deco.Render();
        }

        // undo the knight movement when out of bound
        if (currentKnightWorldPosition.x < 0.0f ||
            currentKnightWorldPosition.x > mapTexture.width * mapScale - windowDimensions[0] ||
            currentKnightWorldPosition.y < 0.0f ||
            currentKnightWorldPosition.y > mapTexture.height * mapScale - windowDimensions[1])
        {
            knight.undoMovement();
        }

        // undo the knight movement when touching decos collision
        const Rectangle &knightCollisionBox = knight.getCollisionBox();
        const Rectangle &aGoblinCollisionBox = aGoblin.getCollisionBox();

        for (auto &deco : decos)
        {
            const Rectangle &decoCollisionBox = deco.getCollisionBox(currentKnightWorldPosition);

            if (CheckCollisionRecs(knightCollisionBox, decoCollisionBox))
            {
                knight.undoMovement();
            }

            if (CheckCollisionRecs(aGoblinCollisionBox, decoCollisionBox))
            {
                aGoblin.undoMovement();
            }
        }

        EndDrawing();
    }

    /// Clean ups
    UnloadTexture(mapTexture);

    CloseWindow();
}
