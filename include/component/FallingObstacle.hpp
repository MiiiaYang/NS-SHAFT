#ifndef FALLINGOBSTACLE_HPP
#define FALLINGOBSTACLE_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
class FallingObstacle : public Util::GameObject{
public:
    explicit FallingObstacle(const std::string &ImagePath) {
        m_ImagePath = ImagePath;
        m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
    }
    void SetImage(const std::string &ImagePath) {
        m_ImagePath = ImagePath;
        m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
    }
    void SetPosition(const glm::vec2 &Position) {
        m_Transform.translation = Position;
    }
    void SetScale(const glm::vec2 &scale) { m_Transform.scale = scale; }
    void SetZIndex(float index) { m_ZIndex = index; }
    glm::vec2 GetPosition() const { return m_Transform.translation; }
    float GetSpeed() const { return m_speed; }
private:
    float m_speed = 2.0f;
    std::string m_ImagePath;
};
#endif //FALLINGOBSTACLE_HPP
