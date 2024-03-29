#ifndef BaseCharacter_H
#define BaseCharacter_H

#include <raylib.h>
#include <raymath.h>
#include "AnimationData.h"

class BaseCharacter
{
private:
protected:
  Texture2D *m_currentTexture{};
  Texture2D m_idleTexture;
  Texture2D m_runningTexture;
  Vector2 m_worldPosition{};
  Vector2 m_lastWorldPosition{};
  float m_xDirection{1.0f};
  float m_speed;
  float m_scale{4.0f};
  AnimationData *m_animData{};
  // of type Rectangle[]
  Rectangle *m_currentRenderPositions{};

  explicit BaseCharacter(
      Texture2D idleTexture,
      Texture2D runningTexture,
      float speed) : m_currentTexture(&m_idleTexture),
                     m_idleTexture(idleTexture),
                     m_runningTexture(runningTexture),
                     m_speed(speed){};

public:
  explicit BaseCharacter();

  ~BaseCharacter();

  // => methods
  virtual void changeMovingDirection(Vector2 &direction) = 0;
  void tick(float currentDeltaTime);
  void render();
  void undoMovement();
  Rectangle getCollisionBox();

  // => getter setters
  // currentTexture
  const Texture2D &getCurrentTexture() const;

  // screenPosition
  virtual const Vector2 getScreenPosition() const = 0;

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