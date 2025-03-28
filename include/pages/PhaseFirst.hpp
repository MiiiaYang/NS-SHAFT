#ifndef PHASE_FIRST_HPP
#define PHASE_FIRST_HPP

#include "App.hpp"
#include "Character.hpp"
#include "component/BasicStairs.hpp"
#include "component/EdgeSpikes.hpp"
#include "component/LevelTitle.hpp"
#include <memory>
#include <vector>

class PhaseFirst : public App {
public:
  std::shared_ptr<Character> m_boy;
  std::vector<std::shared_ptr<BasicStairs>> m_stairs;
  std::shared_ptr<EdgeSpike> spike_up;
  std::shared_ptr<EdgeSpike> spike_down;
  std::vector<std::shared_ptr<EdgeSpike>> m_spikes;
  std::shared_ptr<LevelTitle> m_levelTitle;
  std::vector<std::shared_ptr<BackgroundImage>> m_Background;

  // gravity
  const float m_Gravity = 0.3f;
  float m_VerticalVelocity = 0.0f;
  bool m_IsGrounded = false;
  const float m_GroundLevel = -315.0f;

  explicit PhaseFirst() { phase = Enum::PhaseEnum::PhaseFirst; }

  void Start() override;
  void Update() override;
  void End() override;
};

#endif // PHASE_FIRST_HPP