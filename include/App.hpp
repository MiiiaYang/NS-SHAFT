#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export

#include "AnimatedCharacter.hpp"
#include "Character.hpp"
#include "PhaseResourceManger.hpp"
#include "Util/Renderer.hpp"
#include "Util/Text.hpp"

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

private:
  void ValidTask();

private:
  // std::shared_ptr<Character> m_Giraffe;
  // std::shared_ptr<Character> m_Chest;
  // std::vector<std::shared_ptr<Character>> m_Doors;

  // std::shared_ptr<AnimatedCharacter> m_Bee;
  // std::shared_ptr<AnimatedCharacter> m_Ball;

  // std::shared_ptr<PhaseResourceManger> m_PRM;

  //   bool m_EnterDown = false;
};

#endif
