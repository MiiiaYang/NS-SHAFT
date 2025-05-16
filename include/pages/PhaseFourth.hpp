#ifndef PHASE_FOURTH_HPP
#define PHASE_FOURTH_HPP

#include "Phase.hpp"
#include "component/stairs.hpp"
#include "component/FallingObstacle.hpp"
class PhaseFourth : public Phase {

public:
  int spikeCount = 0;
  std::shared_ptr<Stairs> m_lastDamagingStair = nullptr;
  int m_initialTimer = 0;
  float move_speed = 1.3f;
  std::vector<std::shared_ptr<FallingObstacle>> m_obstacles;

  explicit PhaseFourth() { phase = Enum::PhaseEnum::PhaseFourth; }


  void Start() override;
  void Update() override;
  void End() override;
};

#endif // PHASE_FOURTH_HPP