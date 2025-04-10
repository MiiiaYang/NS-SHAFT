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
      Enum::PhaseEnum::PhaseFirst);
  m_Root.AddChild(m_Button2);

  m_Button1->SetSelected(true);

  m_CurrentState = State::UPDATE;
}

void HomePage::Update() {

  std::vector<ButtonImage *> buttons = {m_Button1.get(), m_Button2.get()};
  ButtonImage::UpdateButtonNavigation(buttons);

  if (Util::Input::IsKeyPressed(Util::Keycode::RETURN)) {
    Enum::PhaseEnum selectedPage = ButtonImage::GetSelectedDestination();
    NavigationTo(selectedPage);
  }

  m_Root.Update();
}

void HomePage::End() {
  phase = Enum::PhaseEnum::HomePage;

  m_CurrentState = State::START;
}
