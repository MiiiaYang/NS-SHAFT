#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"

void App::Update() {

  // // TODO: Add your own logics to finish the tasks in README.md
  // if (Util::Input::IsKeyPressed(Util::Keycode::UP)) {
  //   m_Giraffe->SetPosition(
  //       {m_Giraffe->GetPosition().x, m_Giraffe->GetPosition().y + 3});
  // }
  // if (Util::Input::IsKeyPressed(Util::Keycode::DOWN)) {
  //   m_Giraffe->SetPosition(
  //       {m_Giraffe->GetPosition().x, m_Giraffe->GetPosition().y - 3});
  // }
  // if (Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
  //   m_Giraffe->SetPosition(
  //       {m_Giraffe->GetPosition().x - 3, m_Giraffe->GetPosition().y});
  // }
  // if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
  //   m_Giraffe->SetPosition(
  //       {m_Giraffe->GetPosition().x + 3, m_Giraffe->GetPosition().y});
  // }

  // if (m_Giraffe->IfCollides(m_Chest)) {
  //   m_Root.RemoveChild(m_Chest);
  //   m_Chest->SetVisible(false);
  // }

  // if (m_Phase == Phase::BEE_ANIMATION) {
  //   m_Bee->SetLooping(true);
  // }

  // if (m_Phase == Phase::OPEN_THE_DOORS) {
  //   for (auto door : m_Doors) {
  //     if (door->GetVisibility()) {
  //       if (m_Giraffe->IfCollides(door)) {
  //         door->SetImage(GA_RESOURCE_DIR "/Image/Character/door_open.png");
  //       }
  //     }
  //   }
  // }

  // if (m_Phase == Phase::COUNTDOWN) {
  //   m_Ball->SetVisible(true);
  //   m_Ball->SetLooping(true);
  // }

  // if (m_Phase == Phase::COUNTDOWN && m_Ball->IfAnimationEnds()) {
  //   m_Ball->SetLooping(false);
  // }

  /*
   *  Do not touch the code below as they serve the purpose for validating the
   * tasks, rendering the frame, and exiting the game.
   */

  // if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) ||
  //     Util::Input::IfExit()) {
  //   m_CurrentState = State::END;
  // }

  // if (m_EnterDown) {
  //   if (!Util::Input::IsKeyPressed(Util::Keycode::RETURN)) {
  //     ValidTask();
  //   }
  // }
  // m_EnterDown = Util::Input::IsKeyPressed(Util::Keycode::RETURN);

  // m_Root.Update();
}
