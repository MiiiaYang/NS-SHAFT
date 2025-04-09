#include "App.hpp"
#include "Core/Context.hpp"
#include "Enum.hpp"
#include "Util/Input.hpp"
#include "pages/HomePage.hpp"
#include "pages/PhaseFirst.hpp"
#include "pages/UnlimitPage.hpp"
#include <memory>
#include <vector>

int main(int, char **) {

  auto context = Core::Context::GetInstance();
  auto phases = std::vector<std::shared_ptr<App>>();
  auto currentPhase = Enum::PhaseEnum::HomePage;

  phases.push_back(std::make_shared<HomePage>(HomePage()));
  phases.push_back(std::make_shared<UnlimitPage>(UnlimitPage()));
  phases.push_back(std::make_shared<PhaseFirst>(PhaseFirst()));

  while (!context->GetExit()) {
    auto &phase = phases[static_cast<size_t>(currentPhase)];

    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE)) {
      context->SetExit(true);
      continue;
    }

    if (phase && (phase->GetPhase() != currentPhase)) {
      currentPhase = phase->GetPhase();
      continue;
    }
    switch (phase->GetCurrentState()) {
    case App::State::START:
      phase->Start();
      break;

    case App::State::UPDATE:
      phase->Update();
      break;

    case App::State::END:
      phase->End();
      context->SetExit(true);
      break;
    }
    context->Update();
  }
  return 0;
}
