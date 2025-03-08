#ifndef INSTRUCTIONPAGE_HPP
#define INSTRUCTIONPAGE_HPP

#include "App.hpp"
#include "Character.hpp"

class InstructionPage : public App {
public:
  std::shared_ptr<Character> m_Giraffe;
  std::shared_ptr<Character> m_Chest;

  explicit InstructionPage() { phase = Enum::PhaseEnum::InstructionPage; }

  void Start() override;
  void Update() override;
  void End() override;
};

#endif // INSTRUCTIONPAGE_HPP