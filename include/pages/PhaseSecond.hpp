#ifndef PHASE_SECOND_HPP
#define PHASE_SECOND_HPP

#include "Phase.hpp"
#include "component/stairs.hpp"
class PhaseSecond : public Phase {
public:
  int spikeCount = 0;
  std::shared_ptr<Stairs> m_lastDamagingStair = nullptr;

  explicit PhaseSecond() { phase = Enum::PhaseEnum::PhaseSecond; }

  void Start() override;
  void Update() override;
  void End() override;
};

#endif // PHASE_SECOND_HPP