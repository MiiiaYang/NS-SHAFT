#include "pages/UnlimitPage.hpp"
#include "BackgroundImage.hpp"
#include "component/Text.hpp"
#include <glm/fwd.hpp>
#include <string>

void UnlimitPage::Start() {
  m_Background = std::make_shared<BackgroundImage>();
  m_Background->SetBackground("/background/background.png");
  m_Root.AddChild(m_Background);

  std::shared_ptr<CustomText> m_TaskText = std::make_shared<CustomText>();

  int level = 1;
  std::string text = "第 " + std::to_string(level) + " 關";
  m_TaskText->SetText(text);
  m_TaskText->SetPosition(glm::vec2(-560, 320));
  m_Root.AddChild(m_TaskText);

  m_CurrentState = State::UPDATE;
};

void UnlimitPage::Update() { m_Root.Update(); };

void UnlimitPage::End() {
  // Implementation here
};