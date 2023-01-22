#include "AnimationData.h"

// ctor - dtor
AnimationData::AnimationData(
    int textureFrameColumnsCount,
    int textureFrameRowsCount,
    float textureFrameWidth,
    float textureFrameHeight,
    float updateTime) : m_textureFrameColumnsCount(textureFrameColumnsCount),
                        m_textureFrameRowsCount(textureFrameRowsCount),
                        m_textureFrameWidth(textureFrameWidth),
                        m_textureFrameHeight(textureFrameHeight),
                        m_updateTime(updateTime)
{
  initializeFrameBoundaries();
  m_textureFrameTotalCount = textureFrameColumnsCount * textureFrameRowsCount;
}

AnimationData::~AnimationData()
{
  delete[] m_textureFrameBoundaries;
}

void AnimationData::initializeFrameBoundaries()
{
  m_textureFrameBoundaries = new Rectangle[getTextureFramesCount()];
  for (int xIndex = 0; xIndex < m_textureFrameColumnsCount; xIndex++)
  {
    for (int yIndex = 0; yIndex < m_textureFrameRowsCount; yIndex++)
    {
      m_textureFrameBoundaries[yIndex * m_textureFrameColumnsCount + xIndex] = Rectangle{
          .x{m_textureFrameWidth * xIndex},
          .y{m_textureFrameHeight * yIndex},
          .width{m_textureFrameWidth},
          .height{m_textureFrameHeight}};
    }
  }
  m_currentTextureBoundary = &m_textureFrameBoundaries[0];
}

void AnimationData::update(float currentDeltaTime)
{
  m_runningTime += currentDeltaTime;
  if (m_runningTime >= m_updateTime)
  {
    m_currentTextureBoundary = &(m_textureFrameBoundaries[m_currentFrame]);

    // reset animation stopwatch
    m_runningTime = 0.0;
    // control frame
    m_currentFrame++;
    if (m_currentFrame > m_textureFrameTotalCount - 1)
    {
      m_currentFrame = 0;
    }
  }
}

// => getter setters
const int AnimationData::getTextureFramesCount() const
{
  return m_textureFrameColumnsCount * m_textureFrameRowsCount;
}

// m_textureFrameWidth
const float AnimationData::getTextureFrameWidth() const
{
  return m_textureFrameWidth;
}

// m_textureFrameHeight
const float AnimationData::getTextureFrameHeight() const
{
  return m_textureFrameHeight;
}

// m_currentTextureBoundary
const Rectangle *AnimationData::getCurrentTextureBoundary() const
{
  return m_currentTextureBoundary;
}