#include "AnimationData.h"
#include "Character.h"

// ctor - dtor
Character::Character(
    Texture2D idleTexture,
    Texture2D runningTexture,
    float speed) : BaseCharacter(idleTexture,
                                 runningTexture,
                                 speed){};

// => methods
void Character::updateScreenPosition(int windowWidth, int windowHeight)
{
  m_screenPosition = {
      // texture is too tiny, so scaling it up
      .x{windowWidth / 2.0f - m_scale * (0.5f * (m_animData->getTextureFrameWidth()))},
      .y{windowHeight / 2.0f - m_scale * (0.5f * (m_animData->getTextureFrameHeight()))}};
}

void Character::changeMovingDirection(Vector2 &direction)
{
  if (IsKeyDown(KEY_A))
    direction.x -= 1.0f;
  if (IsKeyDown(KEY_D))
    direction.x += 1.0f;
  if (IsKeyDown(KEY_W))
    direction.y -= 1.0f;
  if (IsKeyDown(KEY_S))
    direction.y += 1.0f;
}
