#include "BaseCharacter.h"

BaseCharacter::BaseCharacter()
{
}

BaseCharacter::~BaseCharacter()
{
  UnloadTexture(m_idleTexture);
  UnloadTexture(m_runningTexture);

  delete[] m_currentRenderPositions;
}

// => methods
void BaseCharacter::updateScreenPosition(int windowWidth, int windowHeight)
{
  m_screenPosition = {
      // *4: texture is too tiny, so scaling it up
      .x{windowWidth / 2.0f - m_scale * (0.5f * (m_animData->getTextureFrameWidth()))},
      .y{windowHeight / 2.0f - m_scale * (0.5f * (m_animData->getTextureFrameHeight()))}};
}

void BaseCharacter::tick(float currentDeltaTime)
{
  // snapshot current world position
  m_lastWorldPosition = m_worldPosition;

  Vector2 direction{};
  changeMovingDirection(direction);

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

  m_currentRenderPositions = new Rectangle[2]{
      // source
      {
          .x{currentTextureBoundary->x},
          .y{currentTextureBoundary->y},
          .width{m_animData->getTextureFrameWidth() * m_xDirection},
          .height{m_animData->getTextureFrameHeight()}},
      // destination
      {
          .x{m_screenPosition.x},
          .y{m_screenPosition.y},
          .width{m_animData->getTextureFrameWidth() * m_scale},
          .height{m_animData->getTextureFrameHeight() * m_scale}}};
}

void BaseCharacter::render()
{
  DrawTexturePro(
      *m_currentTexture,
      m_currentRenderPositions[0],
      m_currentRenderPositions[1],
      Vector2{0, 0},
      0.f,
      WHITE);
}

void BaseCharacter::undoMovement()
{
  m_worldPosition = m_lastWorldPosition;
}

Rectangle BaseCharacter::getCollisionBox()
{
  return Rectangle{
      .x{m_screenPosition.x},
      .y{m_screenPosition.y},
      .width{m_animData->getTextureFrameWidth() * m_scale},
      .height{m_animData->getTextureFrameHeight() * m_scale}};
}

// => getter setters

// currentTexture
const Texture2D &BaseCharacter::getCurrentTexture() const
{
  return *m_currentTexture;
}

// screenPosition
const Vector2 &BaseCharacter::getScreenPosition() const
{
  return m_screenPosition;
}

void BaseCharacter::setScreenPosition(Vector2 &screenPosition)
{
  m_screenPosition = screenPosition;
}

// worldPosition
const Vector2 &BaseCharacter::getWorldPosition() const
{
  return m_worldPosition;
}

// xDirection
const float BaseCharacter::getXDirection() const
{
  return m_xDirection;
}

void BaseCharacter::setXDirection(float xDirection)
{
  m_xDirection = xDirection;
}

// animData
const AnimationData *BaseCharacter::getAnimData() const
{
  return m_animData;
}

void BaseCharacter::setAnimData(AnimationData *animData)
{
  m_animData = animData;
}
