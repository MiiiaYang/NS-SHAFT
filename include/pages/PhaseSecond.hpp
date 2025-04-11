#ifndef PHASE_SECOND_HPP
#define PHASE_SECOND_HPP

#include "Phase.hpp"
class PhaseSecond : public Phase {
public:
  explicit PhaseSecond() { phase = Enum::PhaseEnum::PhaseSecond; }

  void Start() override;
  void Update() override;
  void End() override;
};

#endif // PHASE_SECOND_HPP