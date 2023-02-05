#include "raymath.h"

#include "AnimationData.h"

#ifndef Character_H
#define Character_H

class Character
{
private:
  Texture2D *m_currentTexture{};
  Texture2D m_idleTexture;
  Texture2D m_runningTexture;
  Vector2 m_screenPosition{};
  Vector2 m_worldPosition{};
  Vector2 m_lastWorldPosition{};
  float m_xDirection{1.0f};
  float m_speed;
  float m_scale{4.0f};
  AnimationData *m_animData{};
  // of type Rectangle[]
  Rectangle *m_currentRenderPositions{};

public:
  explicit Character(
      Texture2D idleTexture,
      Texture2D runningTexture,
      float speed);

  ~Character();

  // => methods
  void updateScreenPosition(int windowWidth, int windowHeight);

  void tick(float currentDeltaTime);
  void render();

  void undoMovement();

  Rectangle getCollisionBox();

  // => getter setters
  // currentTexture
  const Texture2D &getCurrentTexture() const;

  // screenPosition
  const Vector2 &getScreenPosition() const;

  void setScreenPosition(Vector2 &screenPosition);
  // worldPosition
  const Vector2 &getWorldPosition() const;

  // xDirection
  const float getXDirection() const;

  void setXDirection(float xDirection);

  // animData
  const AnimationData *getAnimData() const;

  void setAnimData(AnimationData *animData);
};

#endif
