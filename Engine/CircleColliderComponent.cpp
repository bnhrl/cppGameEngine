#include "pch.h"
#include "CircleColliderComponent.h"

#include "Factory.h"
#include "Actor.h"

namespace bnhe {
    bool CircleColliderComponent::CheckCollision(const ColliderComponent& other)
    {
        const CircleColliderComponent* circleCollider = dynamic_cast<const CircleColliderComponent*>(&other);
        if (circleCollider) {
            float distance = GetOwner()->GetTransform().position.DistanceTo(circleCollider->GetOwner()->GetTransform().position);
            return distance <= m_radius + circleCollider->GetRadius();
        }

        //const BoxColliderComponent* boxCollider = dynamic_cast<const BoxColliderComponent*>(&other);

        return false;
    }
    void CircleColliderComponent::Read(const json::value_t& value)
    {
        ColliderComponent::Read(value);

        JSON_READ_NAME(value, "radius", m_radius);
    }
}