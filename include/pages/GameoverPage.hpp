#ifndef GAMEOVERPAGE_HPP
#define GAMEOVERPAGE_HPP
#include "../component/ButtonImage.hpp"
#include "App.hpp"
class GameoverPage : public App {
public:
  std::shared_ptr<ButtonImage> m_Button1;
  std::shared_ptr<ButtonImage> m_Button2;

  explicit GameoverPage() { phase = Enum::PhaseEnum::GameoverPage; }

  void Start(Enum::PhaseEnum lastPhase) override;
  void Update() override;
  void End() override;
};
#endif // GAMEOVERPAGE_HPP
