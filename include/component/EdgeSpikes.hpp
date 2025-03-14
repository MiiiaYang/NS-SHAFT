//
// Created by my100 on 25-3-14.
//

#ifndef EDGESPIKES_HPP
#define EDGESPIKES_HPP
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class EdgeSpike : public Util::GameObject
{
    public:
    explicit EdgeSpike(const std::string &ImagePath)
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
    void SetScale(const glm::vec2 &scale) { m_Transform.scale = scale; }
    private:
        std::string m_ImagePath;
};
#endif //EDGESPIKES_HPP
