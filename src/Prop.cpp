#include <raylib.h>
#include <raymath.h>

#include "Prop.h"

Prop::Prop(Vector2 worldPosition, Texture2D texture)
    : m_worldPosition(worldPosition), m_texture(texture)
{
}

Prop::~Prop()
{
  UnloadTexture(m_texture);
}

void Prop::Render(const Vector2 &knightPosition)
{
  m_screenPosition = Vector2Subtract(
      m_worldPosition,
      knightPosition);

  DrawTextureEx(
      m_texture,
      m_screenPosition,
      0.0f,
      m_scale,
      WHITE);
}

Rectangle Prop::getCollisionBox(const Vector2 &knightPosition)
{
  m_screenPosition = Vector2Subtract(
      m_worldPosition,
      knightPosition);

  return Rectangle{
      .x{m_screenPosition.x},
      .y{m_screenPosition.y},
      .width{m_texture.width * m_scale},
      .height{m_texture.height * m_scale}};
}
