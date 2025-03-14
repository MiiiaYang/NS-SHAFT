#include "pages/PhaseFirst.hpp"
#include "BackgroundImage.hpp"
#include "Character.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"

void PhaseFirst::Start() {
  m_Background = std::make_shared<BackgroundImage>();
  m_Background->SetBackground("/background/background.png");
  m_Root.AddChild(m_Background);

  m_boy = std::make_shared<Character>(GA_RESOURCE_DIR "/character/kid.png");
  m_boy->SetPosition({0.0f, 0.0f});
  m_boy->SetZIndex(50);
  m_boy->SetScale({0.5f, 0.5f});
  m_Root.AddChild(m_boy);

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