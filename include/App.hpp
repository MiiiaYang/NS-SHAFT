#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export
#include "Util/Renderer.hpp"

class App {
public:
  enum class State {
    START,
    UPDATE,
    END,
  };

  State GetCurrentState() const { return m_CurrentState; }

  virtual ~App() = default;

  virtual void Start();

  virtual void Update();

  virtual void End();

  std::shared_ptr<bool> nextPhase;
  Util::Renderer m_Root;
  State m_CurrentState = State::START;
};

#endif
