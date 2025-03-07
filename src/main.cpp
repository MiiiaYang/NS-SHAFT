#include "App.hpp"

#include "Core/Context.hpp"
#include "pages/HomePage.hpp"
#include "pages/InstructionPage.hpp"
#include <memory>
#include <vector>

int main(int, char **) {
  enum class PhaseEnum { HomePage = 0 };

  auto context = Core::Context::GetInstance();
  auto phases = std::vector<std::shared_ptr<App>>();
  auto currentPhase = PhaseEnum::HomePage;

  phases.push_back(std::make_shared<HomePage>(HomePage()));
  phases.push_back(std::make_shared<InstructionPage>(InstructionPage()));

  while (!context->GetExit()) {
    auto &phase = phases[static_cast<size_t>(currentPhase)];
    if (phase->nextPhase && *phase->nextPhase) {
      currentPhase =
          static_cast<PhaseEnum>(static_cast<size_t>(currentPhase) + 1);
      phase->nextPhase = std::make_shared<bool>(false);
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
