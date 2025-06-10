#ifndef UNLIMITPAGE_HPP
#define UNLIMITPAGE_HPP

#include "Phase.hpp"
#include "component/FallingObstacle.hpp"
#include "component/Stairs.hpp"
#include "component/Text.hpp"
class UnlimitPage : public Phase {

public:
  int spikeCount = 0;
  int obstacleTimer = 0;
  std::shared_ptr<Stairs> m_lastDamagingStair = nullptr;
  int m_initialTimer = 0;
  float move_speed = 1.3f;
  bool isBouncing = false;
  int level = 1;
  int frameCounter = 0;
  int levelCounter = 0;

  std::vector<std::shared_ptr<FallingObstacle>> m_obstacles;
  std::shared_ptr<CustomText> m_TaskText;

  explicit UnlimitPage() { phase = Enum::PhaseEnum::UnlimitPage; }

  void Start(Enum::PhaseEnum lastPhase) override;
  void Update() override;
  void End() override;
};

#endif // UnlimitPage_HPP
