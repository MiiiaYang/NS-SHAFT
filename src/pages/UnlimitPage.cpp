#include "pages/UnlimitPage.hpp"
#include "BackgroundImage.hpp"

void UnlimitPage::Start() {
  m_Background = std::make_shared<BackgroundImage>();
  m_Background->SetBackground("/background/background.png");
  m_Root.AddChild(m_Background);

  m_CurrentState = State::UPDATE;
};

void UnlimitPage::Update() { m_Root.Update(); };

void UnlimitPage::End(){
    // Implementation here
};