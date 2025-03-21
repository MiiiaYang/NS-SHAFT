#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>

#include "Util/GameObject.hpp"

class Character : public Util::GameObject {
public:
  explicit Character(const std::string &ImagePath);

  Character(const Character &) = delete;

  Character(Character &&) = delete;

  Character &operator=(const Character &) = delete;

  Character &operator=(Character &&) = delete;

  [[nodiscard]] const std::string &GetImagePath() const { return m_ImagePath; }

  [[nodiscard]] const glm::vec2 &GetPosition() const {
    return m_Transform.translation;
  }

  [[nodiscard]] bool GetVisibility() const { return m_Visible; }

  void SetImage(const std::string &ImagePath);

  void SetPosition(const glm::vec2 &Position) {
    m_Transform.translation = Position;
  }

  void SetScale(const glm::vec2 &scale) { m_Transform.scale = scale; }

  // TODO: Implement the collision detection
  [[nodiscard]] bool IfCollides(const std::shared_ptr<Character> &other) const {
    (void)other;

    if (std::abs(other->GetPosition().x - GetPosition().x) < 10 &&
        std::abs(other->GetPosition().y - GetPosition().y) < 10) {
      return true;
    }

    return false;
  }

  [[nodiscard]] bool IsCollidingWith(const std::shared_ptr<GameObject>& other) const
  {
    if (!other) return false;

    const glm::vec2 thisPos = this->GetTransform().translation;
    const glm::vec2 thisSize = this->GetScaledSize();
    const glm::vec2 otherPos = other->GetTransform().translation;
    const glm::vec2 otherSize = other->GetScaledSize();

    const bool collisionX = thisPos.x - thisSize.x / 2 < otherPos.x + otherSize.x / 2 &&
                  thisPos.x + thisSize.x / 2 > otherPos.x - otherSize.x / 2;

    const bool collisionY = thisPos.y - thisSize.y / 2 < otherPos.y + otherSize.y / 2 &&
                      thisPos.y + thisSize.y / 2 > otherPos.y - otherSize.y / 2;

    return collisionX && collisionY;
  }


  // TODO: Add and implement more methods and properties as needed to finish
  // Giraffe Adventure.

private:
  void ResetPosition() { m_Transform.translation = {0, 0}; }

  std::string m_ImagePath;
};

#endif // CHARACTER_HPP
