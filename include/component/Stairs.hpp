//
// Created by my100 on 25-3-14.
//

#ifndef STAIRS_HPP
#define STAIRS_HPP

#include "Util/Image.hpp"
#include <Util/GameObject.hpp>
#include <memory>
#include <string>

class Stairs : public Util::GameObject {
public:
  enum class StairType { BASE = 0, SPIKE = 1, CRACK = 2 };
  StairType m_Type;
  explicit Stairs(const StairType type,bool Ismoving=false,float direction=1.0f){
    int disappear_countdown = 0;
    m_IsMoving = Ismoving;
    m_Type = type;
    m_direction = direction;
    switch (type) {
    case StairType::BASE:
      m_ImagePath = (GA_RESOURCE_DIR "/stairs/general_stairs.png");
      break;
    case StairType::SPIKE:
      m_ImagePath = (GA_RESOURCE_DIR "/stairs/spiked_stairs.png");
      break;
    case StairType::CRACK:
      disappear_countdown = 180;
      m_ImagePath = (GA_RESOURCE_DIR "/stairs/disappear_stairs.png");
      break;
    }
    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
  }
  void SetImage(const std::string &ImagePath) {
    m_ImagePath = ImagePath;
    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
  }
  void SetPosition(const glm::vec2 &Position) {
    m_Transform.translation = Position;
  }
  void SetScale(const glm::vec2 &scale) { m_Transform.scale = scale; }
  glm::vec2 getPosition() const { return m_Transform.translation; }
  StairType GetType() const { return m_Type; }
  void SetZIndex(float index) { m_ZIndex = index; }
  [[nodiscard]] const glm::vec2 &GetPosition() const {
    return m_Transform.translation;
  }

  bool GetIsMoving() const { return m_IsMoving; }
  float Getdirection() { return m_direction; }
  void SetDirection(float direction) { m_direction = direction; }

private:
  std::string m_ImagePath;
  bool m_IsMoving;
  float m_direction;
};

#endif // STAIRS_HPP
