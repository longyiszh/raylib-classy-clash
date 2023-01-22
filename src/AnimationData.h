#include "raylib.h"

#ifndef AnimationData_H
#define AnimationData_H

class AnimationData
{
private:
  int m_textureFrameColumnsCount;
  int m_textureFrameRowsCount;
  float m_textureFrameWidth{};
  float m_textureFrameHeight{};
  Vector2 m_position{};
  int m_currentFrame{0};
  float m_updateTime;
  float m_runningTime{0};
  Rectangle *m_currentTextureBoundary;
  // of type Rectangle[]
  Rectangle *m_textureFrameBoundaries;
  int m_textureFrameTotalCount;

  void initializeFrameBoundaries();

public:
  explicit AnimationData(
      int textureFrameColumnsCount,
      int textureFrameRowsCount,
      float textureFrameWidth,
      float textureFrameHeight,
      float updateTime);

  ~AnimationData();

  // => methods

  void update(float currentDeltaTime);

  // => getter setters
  const int getTextureFramesCount() const;

  // m_textureFrameWidth
  const float getTextureFrameWidth() const;

  // m_textureFrameHeight
  const float getTextureFrameHeight() const;

  // m_currentTextureBoundary
  const Rectangle *getCurrentTextureBoundary() const;
};

#endif