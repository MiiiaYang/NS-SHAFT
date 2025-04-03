#ifndef BACKGROUND_IMAGE_HPP
#define BACKGROUND_IMAGE_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include <string>

class BackgroundImage : public Util::GameObject {

public:
  BackgroundImage()
      : GameObject(std::make_unique<Util::Image>(GA_RESOURCE_DIR
                                                 "/background/background.png"),
                   -10) {}
  BackgroundImage(const glm::vec2 &Position)
      : GameObject(std::make_unique<Util::Image>(GA_RESOURCE_DIR
                                                 "/background/background.png"),
                   -10, Position) {}
  BackgroundImage(const std::string ImagePath, const glm::vec2 &Position)
      : GameObject(std::make_unique<Util::Image>(GA_RESOURCE_DIR
                                                 "/background/background.png"),
                   -10) {
    SetPosition(Position);
    SetBackground(ImagePath);
  }

  void SetBackground(const std::string &path) {
    auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
    temp->SetImage(ImagePath(path));
  }

  void SetPosition(const glm::vec2 &Position) {
    m_Transform.translation = Position;
  }

  [[nodiscard]] const glm::vec2 &GetPosition() const {
    return m_Transform.translation;
  }

  struct BackGroundSize {
    float height;
    float width;
  };

  BackGroundSize GetSize() {
    auto width = GetScaledSize();
    return {
        width.y,
        width.x,
    };
  }

private:
  inline std::string ImagePath(const std::string &path) {
    return GA_RESOURCE_DIR + path;
  }
};

#endif // BACKGROUND_IMAGE_HPP
