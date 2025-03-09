#include "pages/HomePage.hpp"
#include "BackgroundImage.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "component/ButtonImage.hpp"

void HomePage::Start() {
  m_Background = std::make_shared<BackgroundImage>();
  m_Background->SetBackground("/background/menu_bg.png");
  m_Root.AddChild(m_Background);

  m_Button1 = std::make_shared<ButtonImage>("/menu/unlimit_button.png",
                                            "/menu/unlimit_button_hover.png",
                                            -250, -250, 100, 22);
  m_Button1->SetPosition({-250, -250});
  m_Button1->SetNavigationCallback(
      [this](Enum::PhaseEnum page) { NavigationTo(page); },
      Enum::PhaseEnum::UnlimitPage);
  m_Root.AddChild(m_Button1);

  m_Button2 = std::make_shared<ButtonImage>("/menu/level_button.png",
                                            "/menu/level_button_hover.png", 250,
                                            -250, 100, 22);
  m_Button2->SetPosition({250, -250});
  m_Button2->SetNavigationCallback(
      [this](Enum::PhaseEnum page) { NavigationTo(page); },
      Enum::PhaseEnum::LevelPage);
  m_Root.AddChild(m_Button2);

  // 預設選中 UnlimitPage
  m_Button1->SetSelected(true);

  m_CurrentState = State::UPDATE;
}

void HomePage::Update() {

  if (Util::Input::IsKeyPressed(Util::Keycode::SPACE)) {
    NavigationTo(Enum::PhaseEnum::InstructionPage);
  }

  std::vector<ButtonImage *> buttons = {m_Button1.get(), m_Button2.get()};
  ButtonImage::UpdateButtonNavigation(buttons);

  // **當按下 Enter 時，直接導航到當前選中的按鈕目標頁面**
  if (Util::Input::IsKeyPressed(Util::Keycode::RETURN)) {
    Enum::PhaseEnum selectedPage = ButtonImage::GetSelectedDestination();
    NavigationTo(selectedPage);
  }

  m_Root.Update();
}

void HomePage::End() {
  // 這裡可以加上需要清理的東西
}
