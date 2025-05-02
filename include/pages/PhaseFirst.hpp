#ifndef PHASE_FIRST_HPP
#define PHASE_FIRST_HPP

#include "Phase.hpp"

class PhaseFirst : public Phase {
public:
  explicit PhaseFirst() { phase = Enum::PhaseEnum::PhaseFirst; }
  int m_initialTimer=0;
  void Start() override;
  void Update() override;
  void End() override;
};

#endif // PHASE_FIRST_HPP