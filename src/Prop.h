#ifndef Prop_H
#define Prop_H

#include <raylib.h>

class Prop
{
private:
  Vector2 m_worldPosition{};
  Vector2 m_screenPosition{};
  Texture2D m_texture{};
  float m_scale{4.0f};

public:
  Prop(Vector2 worldPosition, Texture2D texture);
  ~Prop();

  // => methods
  void updateScreenPosition(const Vector2 &knightPosition);
  void Render();
  Rectangle getCollisionBox(const Vector2 &knightPosition);
};

#endif
