#include "pages/PhaseSecond.hpp"
#include "BackgroundImage.hpp"
#include "Character.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"
#include "component/EdgeSpikes.hpp"
#include "component/Stairs.hpp"

#include <algorithm> //(for std::sample)
#include <memory>
#include <random>
#include <vector>

void PhaseSecond::Start() {
  m_LevelMaskTimer = 0;
  m_IsLevelMaskVisible = true;

  m_LevelMask =
      std::make_shared<Image>(GA_RESOURCE_DIR "/level_mask/level2_mask.png");
  m_LevelMask->SetPosition({0.0f, 0.0f});
  m_LevelMask->SetZIndex(100);
  m_Root.AddChild(m_LevelMask);

  m_Background.push_back(std::make_shared<BackgroundImage>(
      "/background/background.png", glm::vec2(0, 0)));
  m_Background.push_back(std::make_shared<BackgroundImage>(
      "/background/background.png",
      glm::vec2(0, -m_Background[0]->GetSize().height)));
  m_Background.push_back(std::make_shared<BackgroundImage>(
      "/background/background.png",
      glm::vec2(0, -2 * m_Background[0]->GetSize().height)));

  for (auto background : m_Background) {
    m_Root.AddChild(background);
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> xPosDis(-115, 115);
  std::uniform_real_distribution<> dis(0, 1);

  int initialStairsCount = 8;
  float startY = 240.0f;
  float yStep = 90.0f;

  m_boy = std::make_shared<Character>(GA_RESOURCE_DIR "/character/kid.png");
  m_boy->SetZIndex(50);
  m_boy->SetScale({0.5f, 0.5f});

  // 隨機生成樓梯
  for (int i = 0; i < initialStairsCount; i++) {
    auto stair = std::make_shared<Stairs>(Stairs::StairType::BASE);
    float xPos = static_cast<float>(xPosDis(gen));
    float yPos = startY - i * yStep;

    stair->SetPosition({xPos, yPos});
    stair->SetZIndex(40);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> scaleDis(
        0.5f, 1.5f); // 寬度縮放範圍 0.5x ~ 1.5x
    float scaleX = scaleDis(gen);

    stair->SetScale({scaleX, 1.0f}); // 只縮放寬度
    m_Root.AddChild(stair);
    m_stairs.push_back(stair);

    if (dis(gen) < 0.3) {
      auto point =
          std::make_shared<PointSystem>(GA_RESOURCE_DIR "/icon/badge.png");
      point->SetPosition({xPos, yPos + 20});
      point->SetZIndex(50);
      m_Root.AddChild(point);
      m_points.push_back(point);
    }

    if (i == 2) {
      m_boy->SetPosition({xPos, yPos + 30.0f});
    }
  }

  m_Root.AddChild(m_boy);

  spike_up =
      std::make_shared<EdgeSpike>(GA_RESOURCE_DIR "/background/spikes_top.png");
  spike_up->SetPosition({10.0f, 345.0f});
  spike_up->SetZIndex(60);
  m_Root.AddChild(spike_up);
  m_spikes.push_back(spike_up);

  spike_down = std::make_shared<EdgeSpike>(GA_RESOURCE_DIR
                                           "/background/spikes_bottom.png");
  spike_down->SetPosition({10.0f, -345.0f});
  spike_down->SetZIndex(60);
  m_Root.AddChild(spike_down);
  m_spikes.push_back(spike_down);

  m_levelTitle = std::make_shared<LevelTitle>(GA_RESOURCE_DIR
                                              "/level_title/level2_title.png");
  m_levelTitle->SetPosition({-470.0f, 260.0f});
  m_Root.AddChild(m_levelTitle);

  m_pointbag = std::make_shared<PointSystem>(GA_RESOURCE_DIR
                                             "/background/achievement_bag.png");
  m_pointbag->SetPosition({-410.0f, -240.0f});
  m_pointbag->SetZIndex(10);
  m_Root.AddChild(m_pointbag);

  m_hpBar = std::make_shared<CharacterHP>(GA_RESOURCE_DIR
                                          "/background/blood_background.png");
  m_hpBar->SetPosition({420.0f, -250.0f});
  m_hpBar->SetZIndex(20);
  m_Root.AddChild(m_hpBar);

  for (int i = 0; i < 5; ++i) {
    auto heart =
        std::make_shared<CharacterHP>(GA_RESOURCE_DIR "/icon/blood_fill.png");
    heart->SetPosition({320.0f + i * 50.0f, -250.0f});
    heart->SetZIndex(25);
    m_Root.AddChild(heart);
    m_hearts.push_back(heart);
  }

  m_lives = 5;
  m_IsInvincible = false;
  m_InvincibleFrame = 0;

  m_CurrentState = State::UPDATE;
};

void PhaseSecond::Update() {
  m_boy->SetImage(GA_RESOURCE_DIR "/character/kid.png");

  // mask
  if (m_IsLevelMaskVisible) {
    m_LevelMaskTimer++;

    if (m_LevelMaskTimer >= 180) { // 假設60fps，3秒為180幀
      m_Root.RemoveChild(m_LevelMask);
      m_IsLevelMaskVisible = false;
      m_levelTitle->SetVisible(true);
    }
    m_Root.Update();
    return;
  }

  // 移動背景
  for (auto background : m_Background) {
    auto pos = background->GetPosition();
    background->SetPosition({pos.x, pos.y + 1.2});
  }

  // 背景循環邏輯
  if (m_Background[0]->GetPosition().y >= m_Background[0]->GetSize().height) {
    m_Background[0]->SetPosition({0, 2 * -m_Background[1]->GetSize().height});
    std::rotate(m_Background.begin(), m_Background.begin() + 1,
                m_Background.end());
  }

  // 樓梯移動
  for (auto stair : m_stairs) {
    auto pos = stair->getPosition();
    stair->SetPosition({pos.x, pos.y + 1.2});
  }

  // 點數向上移動
  for (auto point : m_points) {
    auto pos = point->GetPosition();
    point->SetPosition({pos.x, pos.y + 1.2});
  }

  for (auto it = m_stairs.begin(); it != m_stairs.end();) {
    auto stair = *it;
    auto pos = stair->getPosition();

    if (pos.y > (m_Background[0]->GetSize().height / 2)) {
      m_Root.RemoveChild(stair);
      it = m_stairs.erase(it);
      LOG_DEBUG("remove");
    } else {
      ++it;
    }
  }

  for (auto it = m_points.begin(); it != m_points.end();) {
    auto point = *it;
    auto pos = point->GetPosition();

    if (pos.y > (m_Background[0]->GetSize().height / 2)) {
      m_Root.RemoveChild(point);
      it = m_points.erase(it);
    } else {
      ++it;
    }
  }

  static int frameCounter = 0;
  frameCounter++;

  if (frameCounter >= 80) {
    frameCounter = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);
    std::uniform_int_distribution<> xPosDis(-115, 115);
    std::uniform_real_distribution<float> scaleDis(0.5f, 1.5f);

    if (dis(gen) < 0.6) {
      // 隨機生成樓梯
      auto stairType =
          (dis(gen) < 0.4) ? Stairs::StairType::SPIKE : Stairs::StairType::BASE;

      if (stairType == Stairs::StairType::SPIKE) {
        spikeCount++;
      }

      if (spikeCount > 2) {
        stairType = Stairs::StairType::BASE;
        spikeCount = 0;
      }

      auto stair = std::make_shared<Stairs>(stairType);
      float scaleX = scaleDis(gen);    // 隨機寬度
      stair->SetScale({scaleX, 1.0f}); // 設定樓梯寬度
      stair->SetZIndex(40);
      stair->SetPosition({static_cast<float>(xPosDis(gen)),
                          -(m_Background[0]->GetSize().height / 2 + 50)});
      m_Root.AddChild(stair);
      m_stairs.push_back(stair);

      if (dis(gen) < 0.3) {
        auto point =
            std::make_shared<PointSystem>(GA_RESOURCE_DIR "/icon/badge.png");
        glm::vec2 stairPos = stair->GetPosition();
        point->SetPosition({stairPos.x, stairPos.y + 20});
        point->SetZIndex(50);
        m_Root.AddChild(point);
        m_points.push_back(point);
      }
    }
  }

  glm::vec2 target = m_boy->GetPosition();
  if (Util::Input::IsKeyPressed(Util::Keycode::A)) {
    if ((frameCounter / 5) % 2 == 0) {
      m_boy->SetImage(GA_RESOURCE_DIR "/character/kid_left.png");
    } else {
      m_boy->SetImage(GA_RESOURCE_DIR "/character/kid_leftgo.png");
    }
    target = {target.x - 5, target.y};
  }

  if (Util::Input::IsKeyPressed(Util::Keycode::D)) {
    if ((frameCounter / 5) % 2 == 0) {
      m_boy->SetImage(GA_RESOURCE_DIR "/character/kid_right.png");
    } else {
      m_boy->SetImage(GA_RESOURCE_DIR "/character/kid_rightgo.png");
    }
    target = {target.x + 5, target.y};
  }

  // 地圖邊緣檢查
  if (target.x > -210.000000 + 19 && target.x < 210.000000 - 19 &&
      target.y > -330.000000) {
    m_boy->SetPosition(target);
  }

  // if (m_IsGrounded && Util::Input::IsKeyPressed(Util::Keycode::W)) {
  //   m_VerticalVelocity = 7.0f;
  //   m_IsGrounded = false;
  // }

  // 重力計算
  float posX = m_boy->GetPosition().x;
  float posY = m_boy->GetPosition().y;

  m_VerticalVelocity -= m_Gravity;
  posY += m_VerticalVelocity;

  if (posY <= m_GroundLevel) {
    posY = m_GroundLevel;
    m_VerticalVelocity = 0.0f;
    m_IsGrounded = true;
  } else {
    m_IsGrounded = false;
  }

  bool isOnStair = false;
  std::shared_ptr<Stairs> currentStair = nullptr;

  for (size_t i = 0; i < m_stairs.size(); i++) {
    auto collisionResult = m_boy->IsCollidingWith(m_stairs[i]);
    if (collisionResult.isColliding &&
        collisionResult.side == Character::CollisionSide::Top) {
      isOnStair = true;
      currentStair = m_stairs[i];

      if (currentStair && currentStair->GetType() == Stairs::StairType::SPIKE &&
          currentStair != m_lastDamagingStair && !m_IsInvincible) {
        if (m_lives > 0) {
          --m_lives;
          m_hearts[m_lives]->SetImage(GA_RESOURCE_DIR "/icon/blood_stroke.png");

          m_lastDamagingStair = currentStair;

          m_IsInvincible = true;
          m_InvincibleFrame = m_InvincibleFrameDuration;
        }
      }
      break;
    }
  }

  if (currentStair != m_lastDamagingStair && !isOnStair) {
    m_lastDamagingStair = nullptr;
  }

  if (isOnStair) {
    m_VerticalVelocity = 0.0f;
    m_IsGrounded = true;
    glm::vec2 charPos = m_boy->GetPosition();
    m_boy->SetPosition({charPos.x, charPos.y + 1.2});

  } else if (!m_IsGrounded) {
    m_boy->SetPosition({posX, posY});
  }

  if (Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB)) {
    auto pos = Util::Input::GetCursorPosition();
    LOG_DEBUG(pos);
  }

  if (!m_IsInvincible) {
    for (size_t i = 0; i < m_spikes.size(); i++) {
      if (m_boy->IsCollidingWith(m_spikes[i]).isColliding) {

        if (m_lives > 0) {
          --m_lives;
          m_hearts[m_lives]->SetImage(GA_RESOURCE_DIR "/icon/blood_stroke.png");

          // 啟動無敵模式
          m_IsInvincible = true;
          m_InvincibleFrame = m_InvincibleFrameDuration;
        }
        break;
      }
    }
  }

  if (m_lives == 0) {
    LOG_DEBUG("Player is dead");
    NavigationTo(Enum::PhaseEnum::GameoverPage);
  }

  if (m_boy->IsCollidingWith(m_spikes[1]).isColliding) {
    NavigationTo(Enum::PhaseEnum::GameoverPage);
  }
  if (m_IsInvincible) {
    m_InvincibleFrame--;
    if (m_InvincibleFrame <= 0) {
      m_IsInvincible = false;
    }
  }

  // 檢查角色是否碰到點數
  for (auto it = m_points.begin(); it != m_points.end();) {
    if (m_boy->IsCollidingWith(*it).isColliding) {
      // 更新背包
      m_pointbag->AddPoint();
      // 確保點數完全移除
      m_Root.RemoveChild(*it);
      it = m_points.erase(it); // 從列表中刪除
      LOG_DEBUG("Collide with Point");

    } else {
      ++it;
    }
  }
  if (m_pointbag->GetPointCount() >= 10) {
    NavigationTo(Enum::PhaseEnum::PhaseThird);
  }
  m_Root.Update();
};

void PhaseSecond::End() {
  phase = Enum::PhaseEnum::PhaseSecond;

  m_Root.RemoveChild(m_boy);
  for (auto stair : m_stairs) {
    m_Root.RemoveChild(stair);
  }
  m_stairs.clear();
  m_Root.RemoveChild(spike_up);
  m_Root.RemoveChild(spike_down);
  for (auto spike : m_spikes) {
    m_Root.RemoveChild(spike);
  }
  m_spikes.clear();
  m_Root.RemoveChild(m_levelTitle);
  m_Root.RemoveChild(m_pointbag);
  for (auto point : m_points) {
    m_Root.RemoveChild(point);
  }
  m_points.clear();
  for (auto bg : m_Background) {
    m_Root.RemoveChild(bg);
  }
  m_Background.clear();
  m_Root.RemoveChild(m_hpBar);
  for (auto heart : m_hearts) {
    m_Root.RemoveChild(heart);
  }
  m_hearts.clear();
  m_Root.RemoveChild(m_LevelMask);
  m_CurrentState = App::State::START;
};