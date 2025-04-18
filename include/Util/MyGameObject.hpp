#ifndef UTIL_MYGAMEOBJECT_HPP
#define UTIL_MYGAMEOBJECT_HPP

#include "pch.hpp" // IWYU pragma: export
#include "Util/GameObject.hpp"
#include "Core/Drawable.hpp"

#include "Util/Transform.hpp"


class MyGameObject : protected Util::GameObject{
public:
    Util::Transform m_Transform; // IDC if this should be here.

public:

    /**
 * @brief 檢查當前物件是否與另一個物件碰撞
 * @param other 另一個遊戲物件
 * @return true 如果有碰撞，false 如果沒有
 */
    bool IsCollidingWith(const std::shared_ptr<MyGameObject>& other) const;

protected:

};
#endif
