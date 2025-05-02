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

  struct Size {
    float height;
    float width;
  };

  Size GetSize() {
    auto width = GetScaledSize();
    return {
        width.y,
        width.x,
    };
  }

  // TODO: Implement the collision detection
  [[nodiscard]] bool IfCollides(const std::shared_ptr<Character> &other) const {
    (void)other;

    if (std::abs(other->GetPosition().x - GetPosition().x) < 10 &&
        std::abs(other->GetPosition().y - GetPosition().y) < 10) {
      return true;
    }

    return false;
  }

  enum class CollisionSide { None, Top, Bottom, Left, Right };

  struct CollisionResult {
    bool isColliding;
    CollisionSide side;
  };

  [[nodiscard]] CollisionResult
  IsCollidingWith(const std::shared_ptr<GameObject> &other) const {
    CollisionResult result = {false, CollisionSide::None};

    if (!other)
      return result;

    const glm::vec2 thisPos = this->GetTransform().translation;
    const glm::vec2 thisSize = this->GetScaledSize();
    const glm::vec2 otherPos = other->GetTransform().translation;
    const glm::vec2 otherSize = other->GetScaledSize();

    const bool collisionX =
        thisPos.x - thisSize.x / 2 < otherPos.x + otherSize.x / 2 &&
        thisPos.x + thisSize.x / 2 > otherPos.x - otherSize.x / 2;

    const bool collisionY =
        thisPos.y - thisSize.y / 2 < otherPos.y + otherSize.y / 2 &&
        thisPos.y + thisSize.y / 2 > otherPos.y - otherSize.y / 2;

    result.isColliding = collisionX && collisionY;

    if (result.isColliding) {
      float overlapX =
          std::min(thisPos.x + thisSize.x / 2, otherPos.x + otherSize.x / 2) -
          std::max(thisPos.x - thisSize.x / 2, otherPos.x - otherSize.x / 2);

      float overlapY =
          std::min(thisPos.y + thisSize.y / 2, otherPos.y + otherSize.y / 2) -
          std::max(thisPos.y - thisSize.y / 2, otherPos.y - otherSize.y / 2);

      if (overlapX < overlapY) {
        if (thisPos.x < otherPos.x) {
          result.side = CollisionSide::Left;
        } else {
          result.side = CollisionSide::Right;
        }
      } else {
        if (thisPos.y < otherPos.y) {
          result.side = CollisionSide::Bottom;
        } else {
          result.side = CollisionSide::Top;
        }
      }
    }

    return result;
  }

private:
  void ResetPosition() { m_Transform.translation = {0, 0}; }

  std::string m_ImagePath;
};

#endif // CHARACTER_HPP
