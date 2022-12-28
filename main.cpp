#include "raylib.h"
#include "raymath.h"

struct AnimationData
{
    Rectangle textureBoundary;
    Vector2 position;
    int animationframe;
    float updateTime;
    float runningTime;
};

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

Rectangle *getFrameBoundaries(float frameWidth, float frameHeight, int columnsCount, int rowsCount)
{
    Rectangle *frameBoundaries = new Rectangle[columnsCount * rowsCount];
    for (int xIndex = 0; xIndex < columnsCount; xIndex++)
    {
        for (int yIndex = 0; yIndex < rowsCount; yIndex++)
        {
            frameBoundaries[yIndex * columnsCount + xIndex] = Rectangle{
                .x{frameWidth * xIndex},
                .y{frameHeight * yIndex},
                .width{frameWidth},
                .height{frameHeight}};
        }
    }
    return frameBoundaries;
}

AnimationData updateAnimationData(AnimationData nextAnimData, Rectangle frames[], int animFrameCount, float currentDeltaTime)
{
    nextAnimData.runningTime += currentDeltaTime;
    if (nextAnimData.runningTime >= nextAnimData.updateTime)
    {
        nextAnimData.textureBoundary = frames[nextAnimData.animationframe];

        // reset animation stopwatch
        nextAnimData.runningTime = 0.0;
        // control frame
        nextAnimData.animationframe++;
        if (nextAnimData.animationframe > animFrameCount - 1)
        {
            nextAnimData.animationframe = 0;
        }
    }
    return nextAnimData;
}

int main()
{
    // Window dimension
    const int windowWidth{800};
    const int windowHeight{600};
    InitWindow(windowWidth, windowHeight, "Raylib Classy Clash");

    Texture2D mapTexture{LoadTexture("map/map0.png")};
    Vector2 mapPosition{}; // Will be initialzed to {0.0f, 0.0f}

    // Textures here must have same width and height
    Texture2D knightIdleTexture{LoadTexture("assets/characters/knight_idle_spritesheet.png")};
    Texture2D knightRunningTexture{LoadTexture("assets/characters/knight_run_spritesheet.png")};

    Rectangle knightSource{
        .x{0},
        .y{0},
        .width{knightIdleTexture.width / 6.0f},
        .height{(float)knightIdleTexture.height}};

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

    const int knightFrameColumnsCount{6};
    const int knightFrameRowsCount{1};
    const int knightFrameBoundariesCount{knightFrameColumnsCount * knightFrameRowsCount};

    // Rectangle[]
    Rectangle *knightFrameBoundaries = getFrameBoundaries(
        knightSource.width,
        knightSource.height,
        knightFrameColumnsCount,
        knightFrameRowsCount);

    AnimationData knightAnimData{
        .textureBoundary{knightFrameBoundaries[0]},
        .position{},
        .animationframe{0},
        .updateTime{1.0 / 12.0},
        .runningTime{0}};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // time since last frame
        float deltaTime{GetFrameTime()};

        BeginDrawing();
        ClearBackground(WHITE);

        bool knightIdle{false};
        Texture2D *knightToDrawTexture{};

        Vector2 moveDirection{moveMap(mapPosition)};
        if (moveDirection.x <= -1.0f)
        {
            knightXDirection = -1.0f;
        }
        else if (moveDirection.x >= 1.0f)
        {
            knightXDirection = 1.0f;
        }

        if (moveDirection.x == 0.0f && moveDirection.y == 0.0f)
        {
            knightIdle = true;
        }

        // update knight anim
        knightAnimData = updateAnimationData(
            knightAnimData,
            knightFrameBoundaries,
            knightFrameBoundariesCount,
            deltaTime);

        Rectangle currentKnightSource = knightSource;
        currentKnightSource.x = knightAnimData.textureBoundary.x;
        currentKnightSource.y = knightAnimData.textureBoundary.y;
        currentKnightSource.width *= knightXDirection;

        // draw map
        DrawTextureEx(
            mapTexture,
            mapPosition,
            0.0f,
            4.0f,
            WHITE);

        if (knightIdle)
        {
            knightToDrawTexture = &knightIdleTexture;
        }
        else
        {
            knightToDrawTexture = &knightRunningTexture;
        }

        // draw the knight
        DrawTexturePro(
            *knightToDrawTexture,
            currentKnightSource,
            knightDestination,
            Vector2{0, 0},
            0.f,
            WHITE);

        EndDrawing();
    }

    /// Clean ups
    UnloadTexture(mapTexture);
    UnloadTexture(knightIdleTexture);

    delete[] knightFrameBoundaries;

    CloseWindow();
}
