#include "pages/HomePage.hpp"
#include "BackgroundImage.hpp"
#include "Character.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"

void HomePage::Start() {
  m_Background = std::make_shared<BackgroundImage>();
  m_Background->SetBackground("/background/menu_bg.png");
  m_Root.AddChild(m_Background);

  m_Giraffe = std::make_shared<Character>(GA_RESOURCE_DIR
                                          "/Image/Character/giraffe.png");
  m_Giraffe->SetPosition({-112.5f, -140.5f});
  m_Giraffe->SetZIndex(50);
  m_Root.AddChild(m_Giraffe);

  m_CurrentState = State::UPDATE;
};

void HomePage::Update() {

  if (Util::Input::IsKeyPressed(Util::Keycode::SPACE)) {
    NavigationTo(Enum::PhaseEnum::InstructionPage);
  }

  m_Root.Update();
};

void HomePage::End(){
    // Implementation here
};