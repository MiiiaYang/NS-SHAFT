//
// Created by my100 on 25-3-14.
//

#ifndef BASICSTAIRS_HPP
#define BASICSTAIRS_HPP

#include "Util/Image.hpp"
#include <Util/GameObject.hpp>
#include <string>

class BasicStairs : public Util::GameObject {
public:
  explicit BasicStairs(const std::string &ImagePath) {
    m_ImagePath = ImagePath;
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
  

  [[nodiscard]] const glm::vec2 &GetPosition() const {
    return m_Transform.translation;
  }

private:
  std::string m_ImagePath;

};

#endif // BASICSTAIRS_HPP
