#ifndef POINT_HPP
#define POINT_HPP
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
class Point:public Util::GameObject
{
public:
    explicit Point(const std::string &ImagePath)
    {
        m_ImagePath = ImagePath;
        m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
    }
    void SetImage(const std::string &ImagePath)
    {
        m_ImagePath = ImagePath;
        m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
    }
    void SetPosition(const glm::vec2 &Position) {
        m_Transform.translation = Position;
    }
    void SetScale(const glm::vec2 &scale) {
    m_Transform.scale = scale;
    }
    void SetZIndex(float index) { m_ZIndex = index; }
private:
    std::string m_ImagePath;
};
#endif //POINT_HPP
