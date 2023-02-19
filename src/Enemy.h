#include "AnimationData.h"
#include "BaseCharacter.h"

#ifndef Enemy_H
#define Enemy_H

class Enemy : public BaseCharacter
{
private:
public:
  explicit Enemy(
      // Textures here must have same width and height
      Texture2D idleTexture,
      Texture2D runningTexture,
      float speed);

  // => methods
  void changeMovingDirection(Vector2 &direction) override;

  void updateScreenPosition(int windowWidth, int windowHeight) override;
};

#endif
