#include "pch.h"
#include "Components/CircleColliderComponent.h"

#include "Core/Factory.h"
#include "Framework/Actor.h"

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
        // TODO: Get radius reading working idk why it's not working there should be literally no reason for it to not be working
        JSON_READ_NAME(value, "radius", m_radius);
    }
}