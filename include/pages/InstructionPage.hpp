#include "App.hpp"

class InstructionPage : public App {
public:
  std::shared_ptr<Character> m_Giraffe;
  std::shared_ptr<Character> m_Chest;
  std::shared_ptr<BackgroundImage> m_Background;

  explicit InstructionPage() {}

  void Start() override {
    nextPhase = std::make_shared<bool>(false);
    m_Giraffe = std::make_shared<Character>(GA_RESOURCE_DIR
                                            "/Image/Character/giraffe.png");
    m_Giraffe->SetPosition({-112.5f, -140.5f});
    m_Giraffe->SetZIndex(50);
    m_Root.AddChild(m_Giraffe);

    m_Chest = std::make_shared<Character>(GA_RESOURCE_DIR
                                          "/Image/Character/chest.png");
    m_Chest->SetZIndex(5);
    m_Chest->SetPosition({197.5f, -3.5f});
    m_Chest->SetVisible(false);
    m_Root.AddChild(m_Chest);

    m_Background = std::make_shared<BackgroundImage>();
    m_Background->NextPhase(1);

    m_Root.AddChild(m_Background);

    m_CurrentState = State::UPDATE;
  }

  void Update() override {
    // Implementation here
    m_Root.Update();
  }

  void End() override {
    // Implementation here
  }
};
