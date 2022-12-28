#include "raylib.h"
#include "raymath.h"

/**
 * Instead of moving character on the map,
 * We fix charcter in the middle of the window
 * And move map
 */
Vector2 moveMap(Vector2 &mapPosition)
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
    return direction;
}

int main()
{
    // Window dimension
    const int windowWidth{800};
    const int windowHeight{600};
    InitWindow(windowWidth, windowHeight, "Raylib Classy Clash");

    Texture2D mapTexture{LoadTexture("map/map0.png")};
    Vector2 mapPosition{}; // Will be initialzed to {0.0f, 0.0f}

    Texture2D knightTexture{LoadTexture("assets/characters/knight_idle_spritesheet.png")};

    Rectangle knightSource{
        .x{0},
        .y{0},
        .width{knightTexture.width / 6.0f},
        .height{(float)knightTexture.height}};

    Vector2 knightPosition{
        // *4: texture is too tiny, so scaling it up
        .x{windowWidth / 2.0f - 4 * (0.5f * knightSource.width)},
        .y{windowHeight / 2.0f - 4 * (0.5f * knightSource.height)}};

    Rectangle knightDestination{
        .x{knightPosition.x},
        .y{knightPosition.y},
        .width{knightSource.width * 4},
        .height{knightSource.height * 4}};

    // -1.0f: facing left; 1.0f: facing right
    float knightXDirection{1.0f};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // time since last frame
        float deltaTime{GetFrameTime()};

        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 moveDirection{moveMap(mapPosition)};
        if (moveDirection.x <= -1.0f)
        {
            knightXDirection = -1.0f;
        }
        else if (moveDirection.x >= 1.0f)
        {
            knightXDirection = 1.0f;
        }

        Rectangle currentKnightSource = knightSource;
        currentKnightSource.width *= knightXDirection;

        // draw map
        DrawTextureEx(
            mapTexture,
            mapPosition,
            0.0f,
            4.0f,
            WHITE);

        // draw the knight
        DrawTexturePro(
            knightTexture,
            currentKnightSource,
            knightDestination,
            Vector2{0, 0},
            0.f,
            WHITE);

        EndDrawing();
    }

    /// Clean ups
    UnloadTexture(mapTexture);
    UnloadTexture(knightTexture);

    CloseWindow();
}
