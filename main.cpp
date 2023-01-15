#include "raylib.h"
#include "raymath.h"

class AnimationData
{
private:
    int m_textureFrameColumnsCount;
    int m_textureFrameRowsCount;
    float m_textureFrameWidth{};
    float m_textureFrameHeight{};
    Vector2 m_position{};
    int m_currentFrame{0};
    float m_updateTime;
    float m_runningTime{0};
    Rectangle *m_currentTextureBoundary;
    // of type Rectangle[]
    Rectangle *m_textureFrameBoundaries;
    int m_textureFrameTotalCount;

    void initializeFrameBoundaries()
    {
        m_textureFrameBoundaries = new Rectangle[getTextureFramesCount()];
        for (int xIndex = 0; xIndex < m_textureFrameColumnsCount; xIndex++)
        {
            for (int yIndex = 0; yIndex < m_textureFrameRowsCount; yIndex++)
            {
                m_textureFrameBoundaries[yIndex * m_textureFrameColumnsCount + xIndex] = Rectangle{
                    .x{m_textureFrameWidth * xIndex},
                    .y{m_textureFrameHeight * yIndex},
                    .width{m_textureFrameWidth},
                    .height{m_textureFrameHeight}};
            }
        }
        m_currentTextureBoundary = &m_textureFrameBoundaries[0];
    }

public:
    explicit AnimationData(
        int textureFrameColumnsCount,
        int textureFrameRowsCount,
        float textureFrameWidth,
        float textureFrameHeight,
        float updateTime) : m_textureFrameColumnsCount(textureFrameColumnsCount),
                            m_textureFrameRowsCount(textureFrameRowsCount),
                            m_textureFrameWidth(textureFrameWidth),
                            m_textureFrameHeight(textureFrameHeight),
                            m_updateTime(updateTime)
    {
        initializeFrameBoundaries();
        m_textureFrameTotalCount = textureFrameColumnsCount * textureFrameRowsCount;
    }

    ~AnimationData()
    {
        delete[] m_textureFrameBoundaries;
    }

    // => methods

    void update(float currentDeltaTime)
    {
        m_runningTime += currentDeltaTime;
        if (m_runningTime >= m_updateTime)
        {
            m_currentTextureBoundary = &(m_textureFrameBoundaries[m_currentFrame]);

            // reset animation stopwatch
            m_runningTime = 0.0;
            // control frame
            m_currentFrame++;
            if (m_currentFrame > m_textureFrameTotalCount - 1)
            {
                m_currentFrame = 0;
            }
        }
    }

    // => getter setters
    const int getTextureFramesCount() const
    {
        return m_textureFrameColumnsCount * m_textureFrameRowsCount;
    }

    // m_textureFrameWidth
    const float getTextureFrameWidth() const
    {
        return m_textureFrameWidth;
    }

    // m_textureFrameHeight
    const float getTextureFrameHeight() const
    {
        return m_textureFrameHeight;
    }

    // m_currentTextureBoundary
    const Rectangle *getCurrentTextureBoundary() const
    {
        return m_currentTextureBoundary;
    }
};

class Character
{
private:
    Texture2D *m_currentTexture;
    Texture2D m_idleTexture;
    Texture2D m_runningTexture;
    Vector2 m_screenPosition{};
    Vector2 m_worldPosition{};
    float m_xDirection;
    float m_speed;
    AnimationData *m_animData{};

public:
    explicit Character(
        Texture2D idleTexture,
        Texture2D runningTexture,
        float speed) : m_currentTexture(&m_idleTexture),
                       m_idleTexture(idleTexture),
                       m_runningTexture(runningTexture),
                       m_xDirection(1.0f),
                       m_speed(speed) {}

    ~Character()
    {
        UnloadTexture(m_idleTexture);
        UnloadTexture(m_runningTexture);
    }

    // => methods
    void updateScreenPosition(int windowWidth, int windowHeight)
    {
        m_screenPosition = {
            // *4: texture is too tiny, so scaling it up
            .x{windowWidth / 2.0f - 4 * (0.5f * (m_animData->getTextureFrameWidth()))},
            .y{windowHeight / 2.0f - 4 * (0.5f * (m_animData->getTextureFrameHeight()))}};
    }

    void tick(float currentDeltaTime)
    {
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
            // Add by normalized direction to make the length to be 1
            //    otherwise we would move faster in diagonal directions (sqrt(2))
            m_worldPosition = Vector2Add(m_worldPosition,
                                         Vector2Scale(
                                             Vector2Normalize(direction),
                                             m_speed));
            // flip xDirection
            if (direction.x <= -1.0f)
            {
                m_xDirection = -1.0f;
            }
            else if (direction.x >= 1.0f)
            {
                m_xDirection = 1.0f;
            }

            // apply running texture
            m_currentTexture = &m_runningTexture;
        }
        else
        {
            // apply idle texture
            m_currentTexture = &m_idleTexture;
        }

        m_animData->update(currentDeltaTime);

        const Rectangle *currentTextureBoundary = m_animData->getCurrentTextureBoundary();

        Rectangle currentSource{
            .x{currentTextureBoundary->x},
            .y{currentTextureBoundary->y},
            .width{m_animData->getTextureFrameWidth() * m_xDirection},
            .height{m_animData->getTextureFrameHeight()}};

        const Rectangle currentDestination{
            .x{m_screenPosition.x},
            .y{m_screenPosition.y},
            .width{m_animData->getTextureFrameWidth() * 4},
            .height{m_animData->getTextureFrameHeight() * 4}};

        // draw the chracter
        DrawTexturePro(
            *m_currentTexture,
            currentSource,
            currentDestination,
            Vector2{0, 0},
            0.f,
            WHITE);
    }

    // => getter setters

    // currentTexture
    const Texture2D &getCurrentTexture() const
    {
        return *m_currentTexture;
    }

    // screenPosition
    const Vector2 &getScreenPosition() const
    {
        return m_screenPosition;
    }

    void setScreenPosition(Vector2 &screenPosition)
    {
        m_screenPosition = screenPosition;
    }

    // worldPosition
    const Vector2 &getWorldPosition() const
    {
        return m_worldPosition;
    }

    // xDirection
    const float getXDirection() const
    {
        return m_xDirection;
    }

    void setXDirection(float xDirection)
    {
        m_xDirection = xDirection;
    }

    // animData
    const AnimationData *getAnimData() const
    {
        return m_animData;
    }

    void setAnimData(AnimationData *animData)
    {
        m_animData = animData;
    }
};

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
