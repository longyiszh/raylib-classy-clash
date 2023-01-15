#include "raymath.h"

#include "AnimationData.h"

#ifndef Character_H
#define Character_H

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
  void updateScreenPosition(int windowWidth, int windowHeight);

  void tick(float currentDeltaTime);

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
