#include "pages/PhaseFirst.hpp"
#include "BackgroundImage.hpp"
#include "Character.hpp"
#include "component/basicstairs.hpp"
#include "component/EdgeSpikes.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"
#include <string>
#include <memory>
#include "iostream"

void PhaseFirst::Start() {
  m_Background = std::make_shared<BackgroundImage>();
  m_Background->SetBackground("/background/background.png");
  m_Root.AddChild(m_Background);

  m_boy = std::make_shared<Character>(GA_RESOURCE_DIR "/character/kid.png");
  m_boy->SetPosition({0.0f, 0.0f});
  m_boy->SetZIndex(50);
  m_boy->SetScale({0.5f, 0.5f});
  m_Root.AddChild(m_boy);

  glm::vec2 startPos = glm::vec2(95.0f, 240.0f);
  int stairCount=8;
  bool moveleft = true;
  for (int i=0;i<stairCount;i++)
  {
    auto stair=  std::make_shared<BasicStairs>(GA_RESOURCE_DIR "/stairs/general_stairs.png");
    stair->SetPosition(startPos);

    m_Root.AddChild(stair);
    m_stairs.push_back(stair);
    //count next stairs location
    startPos.y-=70.0f;
    if (moveleft)
    {
      startPos.x=-95.0f;
    }
    else
    {
      startPos.x=95.0f;
    }
    moveleft=!moveleft;
  }

  spike_up=std::make_shared<EdgeSpike>(GA_RESOURCE_DIR "/background/spikes_top.png");
  spike_up->SetPosition({10.0f, 335.0f});
  m_Root.AddChild(spike_up);
  spike_down=std::make_shared<EdgeSpike>(GA_RESOURCE_DIR "/background/spikes_bottom.png");
  spike_down->SetPosition({10.0f, -335.0f});

  m_spikes.push_back(spike_down);
  m_spikes.push_back(spike_up);

  m_levelTitle=std::make_shared<LevelTitle>(GA_RESOURCE_DIR "/level_title/level1_title.png");
  m_levelTitle->SetPosition({-427.0f, 240.0f});
  m_Root.AddChild(m_levelTitle);

  m_CurrentState = State::UPDATE;
};

void PhaseFirst::Update() {
  glm::vec2 target = m_boy->GetPosition();
  if (Util::Input::IsKeyPressed(Util::Keycode::A)) {
    target = {target.x - 5, target.y};
  }

  if (Util::Input::IsKeyPressed(Util::Keycode::D)) {
    target = {target.x + 5, target.y};
  }

  //
  if (Util::Input::IsKeyPressed(Util::Keycode::W)) {
    target = {target.x, target.y+5};
  }
  if (Util::Input::IsKeyPressed(Util::Keycode::S)) {
    target = {target.x, target.y-5};
  }
  //

  if (target.x > -186.000000 && target.x < 210.000000 &&
      target.y > -330.000000 && target.y < 330.000000) {
    m_boy->SetPosition(target);
  }

  // // gravity
  // float posX = m_boy->GetPosition().x;
  // float posY = m_boy->GetPosition().y;
  //
  // m_VerticalVelocity -= m_Gravity;
  // posY += m_VerticalVelocity;
  //
  // if (posY <= m_GroundLevel) {
  //   posY = m_GroundLevel;
  //   m_VerticalVelocity = 0.0f;
  //   m_IsGrounded = true;
  // } else {
  //   m_IsGrounded = false;
  // }

  // m_boy->SetPosition({posX, posY});

  if (m_IsGrounded && Util::Input::IsKeyPressed(Util::Keycode::W)) {
    m_VerticalVelocity = 10.0f;
    m_IsGrounded = false;
  }

  if (Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB)) {
    auto pos = Util::Input::GetCursorPosition();
    LOG_DEBUG(pos);
  }

//樓梯碰撞
  for (size_t i = 0; i < m_stairs.size(); i++)
  {
    if (m_boy->IsCollidingWith(m_stairs[i])) {
      std::cout << "Colliding with stair " << i << std::endl;
    }
  }
  //尖刺陣列碰撞
  for (size_t i = 0; i < m_spikes.size(); i++) {
    if (m_boy->IsCollidingWith(m_spikes[i])) {
      std::cout << "Colliding with spike " << i << std::endl;
    }
  }
  m_Root.Update();
};

void PhaseFirst::End(){
    // Implementation here
};