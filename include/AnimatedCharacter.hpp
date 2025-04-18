#ifndef ANIMATED_CHARACTER_HPP
#define ANIMATED_CHARACTER_HPP

#include <string>
#include <vector>

#include "Util/Animation.hpp"
#include "Util/MyGameObject.hpp"

class AnimatedCharacter : public MyGameObject {

public:
  explicit AnimatedCharacter(const std::vector<std::string> &AnimationPaths);

  [[nodiscard]] bool IsLooping() const {
    return std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->GetLooping();
  }

  [[nodiscard]] bool IsPlaying() const {
    return std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->GetState() ==
           Util::Animation::State::PLAY;
  }

  void SetLooping(bool looping) {
    auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
    temp->SetLooping(looping);
    if (looping) {
      temp->Play();
    } else {
      temp->Pause();
    }
  }

  [[nodiscard]] bool IfAnimationEnds() const;
};

#endif // ANIMATED_CHARACTER_HPP
