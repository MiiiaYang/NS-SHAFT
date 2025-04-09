
#include "Util/TransformUtils.hpp"
#include "Util/MyGameObject.hpp"

bool MyGameObject::IsCollidingWith(const std::shared_ptr<MyGameObject>& other) const {
    if (!other) return false;

    glm::vec2 thisPos = this->GetTransform().translation;
    glm::vec2 thisSize = this->GetScaledSize();
    glm::vec2 otherPos = other->GetTransform().translation;
    glm::vec2 otherSize = other->GetScaledSize();

    bool collisionX = thisPos.x - thisSize.x / 2 < otherPos.x + otherSize.x / 2 &&
                  thisPos.x + thisSize.x / 2 > otherPos.x - otherSize.x / 2;

    bool collisionY = thisPos.y - thisSize.y / 2 < otherPos.y + otherSize.y / 2 &&
                      thisPos.y + thisSize.y / 2 > otherPos.y - otherSize.y / 2;

    return collisionX && collisionY;
}
