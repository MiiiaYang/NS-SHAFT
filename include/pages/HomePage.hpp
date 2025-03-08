#ifndef HOMEPAGE_HPP
#define HOMEPAGE_HPP

#include "App.hpp"
#include "Character.hpp"

class HomePage : public App {
public:
  std::shared_ptr<Character> m_Giraffe;
  std::shared_ptr<Character> m_Chest;

  explicit HomePage() { phase = Enum::PhaseEnum::HomePage; }

  void Start() override;
  void Update() override;
  void End() override;
};

#endif // HOMEPAGE_HPP