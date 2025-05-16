#ifndef PHASE_SECOND_HPP
#define PHASE_SECOND_HPP

#include "Phase.hpp"
#include "component/stairs.hpp"
class PhaseSecond : public Phase {
public:
  int spikeCount = 0;
  std::shared_ptr<Stairs> m_lastDamagingStair = nullptr;
  float move_speed = 1.2f;

  explicit PhaseSecond() { phase = Enum::PhaseEnum::PhaseSecond; }
  int m_initialTimer = 0;
  void Start() override;
  void Update() override;
  void End() override;
};

#endif // PHASE_SECOND_HPP