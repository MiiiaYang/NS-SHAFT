#include "App.hpp"

#include "Core/Context.hpp"
#include "enum.hpp"
#include "pages/HomePage.hpp"
#include "pages/InstructionPage.hpp"
#include <memory>
#include <vector>

int main(int, char **) {

  auto context = Core::Context::GetInstance();
  auto phases = std::vector<std::shared_ptr<App>>();
  auto currentPhase = Enum::PhaseEnum::HomePage;

  phases.push_back(std::make_shared<HomePage>(HomePage()));
  phases.push_back(std::make_shared<InstructionPage>(InstructionPage()));

  while (!context->GetExit()) {
    auto &phase = phases[static_cast<size_t>(currentPhase)];
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
