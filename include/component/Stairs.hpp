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
  enum class StairType { BASE = 0, SPIKE = 1 };
  StairType m_Type;
  explicit Stairs(const StairType type) {
    m_Type = type;
    switch (type) {
    case StairType::BASE:
      m_ImagePath = (GA_RESOURCE_DIR "/stairs/general_stairs.png");
      break;
    case StairType::SPIKE:
      m_ImagePath = (GA_RESOURCE_DIR "/stairs/spiked_stairs.png");
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

  [[nodiscard]] const glm::vec2 &GetPosition() const {
    return m_Transform.translation;
  }

private:
  std::string m_ImagePath;
};

#endif // STAIRS_HPP
