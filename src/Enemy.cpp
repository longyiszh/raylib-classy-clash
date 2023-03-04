#include "Enemy.h"

// ctor - dtor
Enemy::Enemy(
    // Textures here must have same width and height
    Texture2D idleTexture,
    Texture2D runningTexture,
    float speed) : BaseCharacter(idleTexture,
                                 runningTexture,
                                 speed){};

// => methods
void Enemy::changeMovingDirection(Vector2 &direction)
{
  // TODO
}

void Enemy::updateScreenPosition()
{
  m_screenPosition = Vector2Subtract(
      m_worldPosition,
      m_target->getWorldPosition());
}

// => getter setters
Character &Enemy::getTarget(const Character &character) const
{
  return *m_target;
}

void Enemy::setTarget(Character &character)
{
  m_target = &character;
}
