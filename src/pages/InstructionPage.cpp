#include "pages/InstructionPage.hpp"
#include "BackgroundImage.hpp"
#include "Character.hpp"

void InstructionPage::Start() {
  m_Background = std::make_shared<BackgroundImage>();
  m_Background->SetBackground("/background/background.png");
  m_Root.AddChild(m_Background);

  m_Giraffe = std::make_shared<Character>(GA_RESOURCE_DIR
                                          "/Image/Character/giraffe.png");
  m_Giraffe->SetPosition({-60.5f, -140.5f});
  m_Giraffe->SetZIndex(50);
  m_Root.AddChild(m_Giraffe);

  m_CurrentState = State::UPDATE;
};

void InstructionPage::Update() {

  m_Root.Update();
};

void InstructionPage::End(){
    // Implementation here
};