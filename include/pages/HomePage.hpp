#ifndef HOMEPAGE_HPP
#define HOMEPAGE_HPP

#include "../component/ButtonImage.hpp"
#include "App.hpp"

class HomePage : public App {
public:
  std::shared_ptr<ButtonImage> m_Button1;
  std::shared_ptr<ButtonImage> m_Button2;
  int m_initialTimer = 0;

  explicit HomePage() { phase = Enum::PhaseEnum::HomePage; }

  void Start() override;
  void Update() override;
  void End() override;
};

#endif // HOMEPAGE_HPP