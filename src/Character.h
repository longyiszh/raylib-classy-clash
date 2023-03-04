#ifndef Character_H
#define Character_H

#include "AnimationData.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
private:
public:
  explicit Character(
      Texture2D idleTexture,
      Texture2D runningTexture,
      float speed);

  // => methods

  void changeMovingDirection(Vector2 &direction) override;

  void updateScreenPosition(int windowWidth, int windowHeight) override;
};

#endif
