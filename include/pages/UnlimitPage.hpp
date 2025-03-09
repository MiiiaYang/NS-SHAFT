#ifndef UNLIMITPAGE_HPP
#define UNLIMITPAGE_HPP

#include "App.hpp"

class UnlimitPage : public App {
public:
  explicit UnlimitPage() { phase = Enum::PhaseEnum::UnlimitPage; }

  // TODO: Add your game objects here
  // Example: std::shared_ptr<Character> m_Giraffe;

  void Start() override;
  void Update() override;
  void End() override;
};

#endif // UnlimitPage_HPP
