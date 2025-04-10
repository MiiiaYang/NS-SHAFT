#include "pages/GameoverPage.hpp"
#include "BackgroundImage.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "component/ButtonImage.hpp"

void GameoverPage::Start() {
  ButtonImage::ResetSelection();
  m_Background = std::make_shared<BackgroundImage>();
  m_Background->SetBackground("/background/gameover_bg.png");
  m_Root.AddChild(m_Background);

  m_Button1 = std::make_shared<ButtonImage>("/menu/exit_button.png",
                                            "/menu/exit_button_hover.png", -250,
                                            -250, 100, 22);
  m_Button1->SetPosition({-250, -250});
  m_Button1->SetNavigationCallback(Enum::PhaseEnum::HomePage);
  m_Root.AddChild(m_Button1);

  m_Button2 = std::make_shared<ButtonImage>("/menu/Restart_button.png",
                                            "/menu/Restart_button_hover.png",
                                            250, -250, 100, 22);
  m_Button2->SetPosition({250, -250});
  m_Button2->SetNavigationCallback(Enum::PhaseEnum::PhaseFirst);
  m_Root.AddChild(m_Button2);

  m_Button1->SetSelected(true);

  m_CurrentState = State::UPDATE;
}

void GameoverPage::Update() {

  std::vector<ButtonImage *> buttons = {m_Button1.get(), m_Button2.get()};
  ButtonImage::UpdateButtonNavigation(buttons);

  if (Util::Input::IsKeyPressed(Util::Keycode::RETURN)) {
    Enum::PhaseEnum selectedPage = ButtonImage::GetSelectedDestination();
    NavigationTo(selectedPage);
  }

  m_Root.Update();
}

void GameoverPage::End() {}
