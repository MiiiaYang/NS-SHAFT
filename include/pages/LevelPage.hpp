
#ifndef LEVELPAGE_HPP
#define LEVELPAGE_HPP

#include "App.hpp"
#include "Character.hpp"

class LevelPage : public App {
public:
  explicit LevelPage() { phase = Enum::PhaseEnum::LevelPage; }

  std::shared_ptr<Character> m_Giraffe;

  void Start() override;
  void Update() override;
  void End() override;
};

#endif // LEVELPAGE_HPP
