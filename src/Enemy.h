#ifndef Enemy_H
#define Enemy_H

#include "AnimationData.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
private:
  Character *m_target{};

public:
  explicit Enemy(
      // Textures here must have same width and height
      Texture2D idleTexture,
      Texture2D runningTexture,
      float speed);

  // => methods
  void changeMovingDirection(Vector2 &direction) override;

  void updateScreenPosition(int windowWidth, int windowHeight) override;

  // => getter setters
  Character &getTarget(const Character &character) const;
  void setTarget(Character &character);
};

#endif
