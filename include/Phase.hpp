#ifndef PHASE_HPP
#define PHASE_HPP

#include "App.hpp"
#include "Character.hpp"
#include "component/CharacterHP.hpp"
#include "component/EdgeSpikes.hpp"
#include "component/Image.hpp"
#include "component/LevelTitle.hpp"
#include "component/PointSystem.hpp"
#include "component/Stairs.hpp"
#include <memory>
#include <vector>

class Phase : public App {
public:
  std::shared_ptr<Character> m_boy;
  std::vector<std::shared_ptr<Stairs>> m_stairs;
  std::shared_ptr<EdgeSpike> spike_up;
  std::shared_ptr<EdgeSpike> spike_down;
  std::vector<std::shared_ptr<EdgeSpike>> m_spikes;
  std::shared_ptr<LevelTitle> m_levelTitle;
  std::shared_ptr<PointSystem> m_pointbag;
  std::vector<std::shared_ptr<PointSystem>> m_points;
  std::vector<std::shared_ptr<BackgroundImage>> m_Background;
  std::shared_ptr<CharacterHP> m_hpBar;
  std::vector<std::shared_ptr<CharacterHP>> m_hearts;
  std::shared_ptr<Image> m_LevelMask;

  int m_LevelMaskTimer = 0;
  bool m_IsLevelMaskVisible = true;

  int m_lives = 5;
  bool m_IsInvincible = false;
  int m_InvincibleFrame = 0;
  const int m_InvincibleFrameDuration = 60; // 無敵持續 60 幀（大約1秒）

  // gravity
  const float m_Gravity = 0.3f;
  float m_VerticalVelocity = 0.0f;
  bool m_IsGrounded = false;
  const float m_GroundLevel = -315.0f;

  explicit Phase() {}

  void Start(Enum::PhaseEnum lastPhase) override {
    this->lastPhase = lastPhase;
  };
  void Update() override {};
  void End() override {};
};

#endif // PHASE_HPP