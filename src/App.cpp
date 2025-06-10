#include "App.hpp"
#include "Enum.hpp"

void App::Start(Enum::PhaseEnum lastPhase) { this->lastPhase = lastPhase; };
void App::Update() {};
void App::End() {};