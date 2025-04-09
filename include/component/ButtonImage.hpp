#ifndef BUTTON_IMAGE_HPP
#define BUTTON_IMAGE_HPP

#include "../Enum.hpp"
#include "SDL_keyboard.h"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace Enum {
enum class PhaseEnum;
}

class ButtonImage : public Util::GameObject {
public:
  ButtonImage(const std::string &path, const std::string &selectedPath, int x,
              int y, int width, int height)
      : GameObject(std::make_shared<Util::Image>(ImagePath(path)), 0), m_X(x),
        m_Y(y), m_Width(width), m_Height(height), m_DefaultImagePath(path),
        m_SelectedImagePath(selectedPath), m_IsSelected(false) {}

  void SetButtonImage(const std::string &path) {
    m_DefaultImagePath = path;
    if (!m_IsSelected) {
      auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
      if (temp) {
        temp->SetImage(ImagePath(path));
      }
    }
  }

  void SetSelectedButtonImage(const std::string &path) {
    m_SelectedImagePath = path;
    if (m_IsSelected) {
      auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
      if (temp) {
        temp->SetImage(ImagePath(path));
      }
    }
  }

  void SetNavigationCallback(std::function<void(Enum::PhaseEnum)> callback,
                             Enum::PhaseEnum destination) {
    m_NavigationCallback = std::move(callback);
    m_Destination = destination;
  }

  void SetPosition(const glm::vec2 &Position) {
    m_Transform.translation = Position;
  }

  void SetSelected(bool selected) {
    if (m_IsSelected != selected) {
      m_IsSelected = selected;
      if (selected) {
        s_SelectedDestination = m_Destination;
      }
      auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
      if (temp) {
        temp->SetImage(
            ImagePath(m_IsSelected ? m_SelectedImagePath : m_DefaultImagePath));
      }
    }
  }

  bool IsSelected() const { return m_IsSelected; }

  int GetX() const { return m_X; }

  static Enum::PhaseEnum GetSelectedDestination() {
    return s_SelectedDestination;
  }

  static void UpdateButtonNavigation(std::vector<ButtonImage *> &buttons) {
    if (buttons.empty())
      return;

    std::sort(
        buttons.begin(), buttons.end(),
        [](ButtonImage *a, ButtonImage *b) { return a->GetX() < b->GetX(); });

    auto selectedIt =
        std::find_if(buttons.begin(), buttons.end(),
                     [](ButtonImage *btn) { return btn->IsSelected(); });

    size_t selectedIndex = 0;
    if (selectedIt != buttons.end()) {
      selectedIndex = selectedIt - buttons.begin();
    } else if (!buttons.empty()) {
      buttons[0]->SetSelected(true);
    }

    // 按 D 鍵 → 選中右邊按鈕 (Level)
    if (IsKeyJustPressed(SDL_SCANCODE_D) && selectedIndex == 0) {
      buttons[selectedIndex]->SetSelected(false);
      buttons[selectedIndex + 1]->SetSelected(true);
    }

    // 按 A 鍵 → 選中左邊按鈕 (Unlimit)
    if (IsKeyJustPressed(SDL_SCANCODE_A) && selectedIndex == 1) {
      buttons[selectedIndex]->SetSelected(false);
      buttons[selectedIndex - 1]->SetSelected(true);
    }

    UpdatePreviousKeyState();
  }

private:
  static inline Enum::PhaseEnum s_SelectedDestination =
      Enum::PhaseEnum::UnlimitPage;

  std::function<void(Enum::PhaseEnum)> m_NavigationCallback;
  Enum::PhaseEnum m_Destination;
  int m_X, m_Y, m_Width, m_Height;
  std::string m_DefaultImagePath;
  std::string m_SelectedImagePath;
  bool m_IsSelected;

  static inline Uint8 s_PreviousKeyState[SDL_NUM_SCANCODES] = {0};

  inline std::string ImagePath(const std::string &path) {
    return GA_RESOURCE_DIR + path;
  }

  static bool IsKeyJustPressed(SDL_Scancode scancode) {
    const Uint8 *currentKeyState = SDL_GetKeyboardState(NULL);
    return currentKeyState[scancode] && !s_PreviousKeyState[scancode];
  }

  static void UpdatePreviousKeyState() {
    const Uint8 *currentKeyState = SDL_GetKeyboardState(NULL);
    memcpy(s_PreviousKeyState, currentKeyState,
           sizeof(Uint8) * SDL_NUM_SCANCODES);
  }
};

#endif // BUTTON_IMAGE_HPP
