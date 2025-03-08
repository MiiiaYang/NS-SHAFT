#ifndef HOMEPAGE_HPP
#define HOMEPAGE_HPP

#include "App.hpp"
#include "BackgroundImage.hpp"
#include "Character.hpp"

class HomePage : public App {
public:
  std::shared_ptr<Character> m_Giraffe;
  std::shared_ptr<Character> m_Chest;
  std::shared_ptr<BackgroundImage> m_Background;

  explicit HomePage() {}

  void Start() override;
  void Update() override;
  void End() override;
};

#endif // HOMEPAGE_HPP