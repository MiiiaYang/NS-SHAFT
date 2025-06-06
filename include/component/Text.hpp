#ifndef CUSTOMTEXT_HPP
#define CUSTOMTEXT_HPP

#include "Util/GameObject.hpp"
#include "Util/Text.hpp"
#include <memory>
#include <string>

class CustomText : public Util::GameObject {
public:
  CustomText()
      : GameObject(std::make_unique<Util::Text>(
                       GA_RESOURCE_DIR "/Font/RampartOne-Regular.ttf", 40,
                       "None", Util::Color::FromName(Util::Colors::ORANGE)),
                   100) {
    m_Transform.translation = {0.0F, 0.0F};
  }

  void SetText(std::string text) {
    auto temp = std::dynamic_pointer_cast<Util::Text>(m_Drawable);
    temp->SetText(text);
  }

  void SetPosition(const glm::vec2 &position) {
    m_Transform.translation = position;
  }
};

#endif // CUSTOMTEXT_HPP