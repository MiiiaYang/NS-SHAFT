#include "App.hpp"
#include "Core/Context.hpp"
#include "Enum.hpp"
#include "Util/Input.hpp"
#include "pages/GameoverPage.hpp"
#include "pages/HomePage.hpp"
#include "pages/PhaseFirst.hpp"
#include "pages/PhaseFourth.hpp"
#include "pages/PhaseSecond.hpp"
#include "pages/PhaseThird.hpp"
#include "pages/UnlimitPage.hpp"
#include <memory>
#include <vector>

#include "pages/AllPassPage.hpp"
#include "pages/PhaseFifth.hpp"

int main(int, char **) {

  auto context = Core::Context::GetInstance();
  auto phases = std::vector<std::shared_ptr<App>>();
  auto currentPhase = Enum::PhaseEnum::HomePage;
  auto lastPhase = Enum::PhaseEnum::HomePage;

  phases.push_back(std::make_shared<HomePage>(HomePage()));
  phases.push_back(std::make_shared<UnlimitPage>(UnlimitPage()));
  phases.push_back(std::make_shared<PhaseFirst>(PhaseFirst()));
  phases.push_back(std::make_shared<PhaseSecond>(PhaseSecond()));
  phases.push_back(std::make_shared<GameoverPage>(GameoverPage()));
  phases.push_back(std::make_shared<PhaseThird>(PhaseThird()));
  phases.push_back(std::make_shared<PhaseFourth>(PhaseFourth()));
  phases.push_back(std::make_shared<PhaseFifth>(PhaseFifth()));
  phases.push_back(std::make_shared<AllPassPage>(AllPassPage()));
  while (!context->GetExit()) {
    auto &phase = phases[static_cast<size_t>(currentPhase)];

    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE)) {
      context->SetExit(true);
      continue;
    }

    if (phase && (phase->GetPhase() != currentPhase)) {
      lastPhase = currentPhase;
      currentPhase = phase->GetPhase();
    }

    switch (phase->GetCurrentState()) {
    case App::State::START:
      phase->Start(lastPhase);
      break;

    case App::State::UPDATE:
      phase->Update();
      break;

    case App::State::END:
      phase->End();
      break;
    }
    context->Update();
  }
  return 0;
}
