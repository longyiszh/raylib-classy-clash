#include "AnimationData.h"
#include "Character.h"

// ctor - dtor
Character::Character(
    Texture2D idleTexture,
    Texture2D runningTexture,
    float speed) : m_currentTexture(&m_idleTexture),
                   m_idleTexture(idleTexture),
                   m_runningTexture(runningTexture),
                   m_speed(speed) {}

Character::~Character()
{
  UnloadTexture(m_idleTexture);
  UnloadTexture(m_runningTexture);
}

// => methods
void Character::updateScreenPosition(int windowWidth, int windowHeight)
{
  m_screenPosition = {
      // *4: texture is too tiny, so scaling it up
      .x{windowWidth / 2.0f - m_scale * (0.5f * (m_animData->getTextureFrameWidth()))},
      .y{windowHeight / 2.0f - m_scale * (0.5f * (m_animData->getTextureFrameHeight()))}};
}

void Character::tick(float currentDeltaTime)
{
  // snapshot current world position
  m_lastWorldPosition = m_worldPosition;

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
      .width{m_animData->getTextureFrameWidth() * m_scale},
      .height{m_animData->getTextureFrameHeight() * m_scale}};

  // draw the chracter
  DrawTexturePro(
      *m_currentTexture,
      currentSource,
      currentDestination,
      Vector2{0, 0},
      0.f,
      WHITE);
}

void Character::undoMovement()
{
  m_worldPosition = m_lastWorldPosition;
}

// => getter setters

// currentTexture
const Texture2D &Character::getCurrentTexture() const
{
  return *m_currentTexture;
}

// screenPosition
const Vector2 &Character::getScreenPosition() const
{
  return m_screenPosition;
}

void Character::setScreenPosition(Vector2 &screenPosition)
{
  m_screenPosition = screenPosition;
}

// worldPosition
const Vector2 &Character::getWorldPosition() const
{
  return m_worldPosition;
}

// xDirection
const float Character::getXDirection() const
{
  return m_xDirection;
}

void Character::setXDirection(float xDirection)
{
  m_xDirection = xDirection;
}

// animData
const AnimationData *Character::getAnimData() const
{
  return m_animData;
}

void Character::setAnimData(AnimationData *animData)
{
  m_animData = animData;
}