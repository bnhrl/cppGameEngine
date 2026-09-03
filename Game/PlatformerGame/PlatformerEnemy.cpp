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

const float EPSILON = 1.f;
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

    if (m_jump > 0.f)
    {
        m_jump -= delta * 100000.f;
        m_physicsComponent->ApplyForce(Vector2(0.f, -m_jump));
    }

    if (m_physicsComponent->GetVelocity().x < -EPSILON)      m_spriteComponent->SetFlipH();
    else if (m_physicsComponent->GetVelocity().x > EPSILON) m_spriteComponent->SetFlipH(false);

    Actor::Update(delta);
}

void PlatformerEnemy::OnCollision(Actor* actor)
{
    if (actor->HasTag("DamagesEnemy")) Destroy();
    if (actor->HasTag("Bouncer")) m_jump = 10000.f;
}