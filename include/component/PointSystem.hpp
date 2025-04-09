//
// Created by my100 on 25-3-21.
//

#ifndef POINTSYSTEM_HPP
#define POINTSYSTEM_HPP
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "component/Point.hpp"
#include <memory>

class PointSystem : public Util::GameObject {
public:
  explicit PointSystem(const std::string &ImagePath) {
    m_ImagePath = ImagePath;
    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
    m_PointCount = 0;
    m_MaxSlots = 10; // 初始化最多 10 個點數
  }
  void SetImage(const std::string &ImagePath) {
    m_ImagePath = ImagePath;
    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
  }
  void SetPosition(const glm::vec2 &Position) {
    m_Transform.translation = Position;
  }
  void SetScale(const glm::vec2 &scale) { m_Transform.scale = scale; }

  void SetZIndex(float index) { m_ZIndex = index; }

  void AddPoint() {
    if (m_PointCount < m_MaxSlots) {
      m_PointCount++;
    }
    glm::vec2 slotPos = GetSlotPosition(m_PointCount - 1); // 計算點數顯示位置
    auto newPoint = std::make_shared<Point>(GA_RESOURCE_DIR "/icon/badge.png");
    newPoint->SetPosition(slotPos);
    newPoint->SetZIndex(20);
    AddChild(newPoint);
  }

  glm::vec2 GetPosition() const { return m_Transform.translation; }

private:
  std::string m_ImagePath;
  int m_PointCount; // 存放已收集的點數
  int m_MaxSlots;

  // 計算背包內點數位置
  glm::vec2 GetSlotPosition(int index) {
    float startX = -525.0f; // 第一個格子的起始 X 位置
    float startY = -207.0f; // Y 位置固定
    float spacing = 57.0f;  // 格子間距
    if (index >= 5) {
      startY = -273.0f;
    }
    return {startX + (index % 5) * spacing, startY};
  }
};
#endif // POINTSYSTEM_HPP
