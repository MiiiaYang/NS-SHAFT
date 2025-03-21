#include "pages/PhaseFirst.hpp"
#include "BackgroundImage.hpp"
#include "Character.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"
#include "component/BasicStairs.hpp"
#include "component/EdgeSpikes.hpp"
#include <memory>
#include "iostream"
#include <string>
#include <random>
#include <algorithm>  //(for std::sample)
void PhaseFirst::Start() {
  m_Background = std::make_shared<BackgroundImage>();
  m_Background->SetBackground("/background/background.png");
  m_Root.AddChild(m_Background);

  m_boy = std::make_shared<Character>(GA_RESOURCE_DIR "/character/kid.png");
  m_boy->SetPosition({86.0f, 300.0f});
  m_boy->SetZIndex(50);
  m_boy->SetScale({0.5f, 0.5f});
  m_Root.AddChild(m_boy);

  glm::vec2 startPos = glm::vec2(95.0f, 240.0f);
  int stairCount = 8;
  bool moveleft = true;

  for (int i = 0; i < stairCount; i++) {
    auto stair = std::make_shared<BasicStairs>(GA_RESOURCE_DIR
                                               "/stairs/general_stairs.png");
    stair->SetPosition(startPos);

    m_Root.AddChild(stair);
    m_stairs.push_back(stair);
    startPos.y -= 70.0f;
    if (moveleft) {
      startPos.x = -95.0f;
    } else {
      startPos.x = 95.0f;
    }
    moveleft = !moveleft;
  }

  spike_up =
      std::make_shared<EdgeSpike>(GA_RESOURCE_DIR "/background/spikes_top.png");
  spike_up->SetPosition({10.0f, 335.0f});
  m_Root.AddChild(spike_up);
  spike_down = std::make_shared<EdgeSpike>(GA_RESOURCE_DIR
                                           "/background/spikes_bottom.png");
  spike_down->SetPosition({10.0f, -335.0f});
  m_Root.AddChild(spike_down);

  m_spikes.push_back(spike_down);
  m_spikes.push_back(spike_up);


  m_levelTitle=std::make_shared<LevelTitle>(GA_RESOURCE_DIR "/level_title/level1_title.png");
  m_levelTitle->SetPosition({-470.0f, 260.0f});
  m_Root.AddChild(m_levelTitle);

  m_pointbag=std::make_shared<PointSystem>(GA_RESOURCE_DIR "/background/achievement_bag.png");
  m_pointbag->SetPosition({-410.0f, -240.0f});
  m_pointbag->SetZIndex(10);
  m_Root.AddChild(m_pointbag);

  //PointSystem
  // 隨機選擇 () 個樓梯來放置點數
  int totalPoints =5;
  std::vector<std::shared_ptr<BasicStairs>> selectedStairs;  // 存放選中的樓梯

  std::random_device rd;  // 隨機
  std::mt19937 gen(rd());  // 使用 Mersenne Twister 隨機數生成器
  std::sample(m_stairs.begin(), m_stairs.end(), std::back_inserter(selectedStairs), totalPoints, gen);
  // `std::sample()` 會從 `m_stairs` 中隨機選出 `totalPoints` 個不重複的元素
  for (auto& stair : selectedStairs) {  // 遍歷選出的樓梯
    auto point = std::make_shared<PointSystem>(GA_RESOURCE_DIR "/icon/badge.png");  // 創建點數
    glm::vec2 stairPos = stair->GetPosition();  // 取得樓梯位置

    // 設定點數的位置 (略高於樓梯)
    point->SetPosition({stairPos.x, stairPos.y + 20});
    m_Root.AddChild(point);  // 加入場景
    m_points.push_back(point);  // 存入點數列表
  }
  m_CurrentState = State::UPDATE;
};

void PhaseFirst::Update() {
  glm::vec2 target = m_boy->GetPosition();
  if (Util::Input::IsKeyPressed(Util::Keycode::A)) {
    target = {target.x - 5, target.y};
  }

  if (Util::Input::IsKeyPressed(Util::Keycode::D)) {
    target = {target.x + 5, target.y};
  }


  // 地圖邊緣
  if (target.x > -186.000000 + 19 && target.x < 210.000000 - 19 &&

      target.y > -330.000000 && target.y < 330.000000) {
    m_boy->SetPosition(target);
  }
  
  // if (m_IsGrounded && Util::Input::IsKeyPressed(Util::Keycode::W)) {
  //   m_VerticalVelocity = 7.0f;
  //   m_IsGrounded = false;
  // }

  // gravity
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

  // 樓梯碰撞
  auto isOnStair = false;
  for (size_t i = 0; i < m_stairs.size(); i++) {
    auto collisionResult = m_boy->IsCollidingWith(m_stairs[i]);
    if (collisionResult.isColliding &&
        collisionResult.side == Character::CollisionSide::Top) {
      isOnStair = true;
      break;
    } else if (collisionResult.isColliding &&
               collisionResult.side == Character::CollisionSide::Bottom) {
      LOG_DEBUG("Botto");
    } else {
      isOnStair = false;
    }
  }

  if (isOnStair) {
    m_VerticalVelocity = 0.0f;
    m_IsGrounded = true;
  }

  if (!isOnStair && !m_IsGrounded) {
    m_boy->SetPosition({posX, posY});
  }

  if (Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB)) {
    auto pos = Util::Input::GetCursorPosition();
    LOG_DEBUG(pos);
  }

  // 尖刺陣列碰撞
  for (size_t i = 0; i < m_spikes.size(); i++) {
    if (m_boy->IsCollidingWith(m_spikes[i]).isColliding) {
      LOG_DEBUG("Collide with spike");

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


  m_Root.Update();
};

void PhaseFirst::End(){
    // Implementation here
};