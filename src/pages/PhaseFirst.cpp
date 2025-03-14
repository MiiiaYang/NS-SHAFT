#include "pages/PhaseFirst.hpp"
#include "BackgroundImage.hpp"
#include "Character.hpp"
#include "component/basicstairs.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"
#include <string>
#include <memory>

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
    auto stair=  std::make_shared<basicstairs>(GA_RESOURCE_DIR "/stairs/general_stairs.png");
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
  m_CurrentState = State::UPDATE;
};

void PhaseFirst::Update() {
  if (Util::Input::IsKeyPressed(Util::Keycode::A)) {
    m_boy->SetPosition({m_boy->GetPosition().x - 5, m_boy->GetPosition().y});
  }

  if (Util::Input::IsKeyPressed(Util::Keycode::D)) {
    m_boy->SetPosition({m_boy->GetPosition().x + 5, m_boy->GetPosition().y});
  }

  // gravity
  float posX = m_boy->GetPosition().x;
  float posY = m_boy->GetPosition().y;

  m_VerticalVelocity -= m_Gravity;
  posY += m_VerticalVelocity;

  if (posY <= m_GroundLevel) {
    posY = m_GroundLevel;
    m_VerticalVelocity = 0.0f;
    m_IsGrounded = true;
  } else {
    m_IsGrounded = false;
  }

  m_boy->SetPosition({posX, posY});

  if (m_IsGrounded && Util::Input::IsKeyPressed(Util::Keycode::W)) {
    m_VerticalVelocity = 10.0f;
    m_IsGrounded = false;
  }

  if (Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB)) {
    auto pos = Util::Input::GetCursorPosition();
    LOG_DEBUG(pos);
  }

  m_Root.Update();
};

void PhaseFirst::End(){
    // Implementation here
};