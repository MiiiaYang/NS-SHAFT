#ifndef APP_HPP
#define APP_HPP

#include "BackgroundImage.hpp"
#include "Enum.hpp"
#include "Util/Renderer.hpp"
#include "pch.hpp" // IWYU pragma: export
#include <memory>

class App {
public:
  enum class State {
    START,
    UPDATE,
    END,
  };

  State GetCurrentState() const { return m_CurrentState; }
  Enum::PhaseEnum GetPhase() const { return phase; }

  virtual ~App() = default;

  virtual void Start(Enum::PhaseEnum lastPhase);

  virtual void Update();

  virtual void End();

  void NavigationTo(Enum::PhaseEnum phase) {
    m_CurrentState = State::END;
    this->phase = phase;
  }

  Enum::PhaseEnum phase;
  Enum::PhaseEnum lastPhase;
  Util::Renderer m_Root;
  State m_CurrentState = State::START;
  std::shared_ptr<BackgroundImage> m_Background;
};

#endif
