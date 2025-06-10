#ifndef AllPassPage_HPP
#define AllPassPage_HPP
#include "../component/ButtonImage.hpp"
#include "App.hpp"
class AllPassPage : public App {
public:
  std::shared_ptr<ButtonImage> m_Button1;
  std::shared_ptr<ButtonImage> m_Button2;

  explicit AllPassPage() { phase = Enum::PhaseEnum::AllPassPage; }

  void Start(Enum::PhaseEnum lastPhase) override;
  void Update() override;
  void End() override;
};
#endif // AllPassPage_HPP