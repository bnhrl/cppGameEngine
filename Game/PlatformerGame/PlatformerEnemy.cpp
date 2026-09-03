#include "PlatformerEnemy.h"

#include "Core/Factory.h"

FACTORY_REGISTER(PlatformerEnemy);

void PlatformerEnemy::OnStart()
{
    Actor::OnStart();

    m_physicsComponent = GetComponent<PhysicsComponent>();
    assert(m_physicsComponent);
    m_spriteComponent = GetComponent<SpriteAnimatorRendererComponent>();
    assert(m_spriteComponent);
}

void PlatformerEnemy::Update(float delta)
{
    if (!m_target)
    {
        m_physicsComponent->SetVelocity(Vector2(0.f, GetVelocity().y));
        return;
    }

    Vector2 direction = GetTransform().position.DirectionTo(m_target->GetTransform().position);
    m_physicsComponent->SetVelocity({ direction.x * -m_speed, GetVelocity().y });
    m_physicsComponent->SetRotation(0.f);

    Actor::Update(delta);
}
