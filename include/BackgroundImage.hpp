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

  void SetBackground(const std::string &path) {
    auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
    temp->SetImage(ImagePath(path));
  }

private:
  inline std::string ImagePath(const std::string &path) {
    return GA_RESOURCE_DIR + path;
  }
};

#endif // BACKGROUND_IMAGE_HPP
