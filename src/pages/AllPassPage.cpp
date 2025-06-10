#include "pages/AllPassPage.hpp"
#include "BackgroundImage.hpp"
#include "Enum.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "component/ButtonImage.hpp"

void AllPassPage::Start(Enum::PhaseEnum lastPhase) {
    this->lastPhase = lastPhase;
    m_Background = std::make_shared<BackgroundImage>();
    m_Background->SetBackground("/background/AllPass_bg.png");
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

void AllPassPage::Update() {

    std::vector<ButtonImage *> buttons = {m_Button1.get(), m_Button2.get()};
    ButtonImage::UpdateButtonNavigation(buttons);

    if (Util::Input::IsKeyPressed(Util::Keycode::RETURN)) {
        Enum::PhaseEnum selectedPage = ButtonImage::GetSelectedDestination();
        NavigationTo(selectedPage);
    }

    m_Root.Update();
}

void AllPassPage::End() {
    phase = Enum::PhaseEnum::AllPassPage;

    m_Root.RemoveChild(m_Background);
    m_Root.RemoveChild(m_Button1);
    m_Root.RemoveChild(m_Button2);
    m_Background.reset();
    m_Button1.reset();
    m_Button2.reset();

    m_CurrentState = State::START;
}
