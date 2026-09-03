#include "pch.h"
#include "PlatformerPlayer.h"

#include "Engine.h"

FACTORY_REGISTER(PlatformerPlayer)

void PlatformerPlayer::OnStart()
{
    Actor::OnStart();

    m_physicsComponent = GetComponent<PhysicsComponent>();
    assert(m_physicsComponent);
    m_spriteComponent = GetComponent<SpriteAnimatorRendererComponent>();
    assert(m_spriteComponent);
}

void PlatformerPlayer::Update(float delta)
{
    // Input
    Vector2 direction = Vector2(0.f,0.f);
    if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_LEFT)) direction.x = -1.f;
    else if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_RIGHT)) direction.x = 1.f;

    // Movement
    m_physicsComponent->SetVelocity({ direction.x * m_speed, m_physicsComponent->GetVelocity().y });
    m_physicsComponent->SetRotation(0.f);

    //if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE) && m_jump <= 0.f) m_jump = 100000.f;
    if (m_jump > 0.f)
    {
        m_jump -= delta * 100000.f;
        m_physicsComponent->ApplyForce(Vector2(0.f, -m_jump));
        //m_physicsComponent->SetVelocity(Vector2(m_physicsComponent->GetVelocity().x, -m_jump));
    }

    Actor::Update(delta);
}

const float EPSILON = 1.f;
void PlatformerPlayer::Draw(const Renderer& renderer)
{
    // Animation
    if (m_physicsComponent->GetVelocity().x >= EPSILON || m_physicsComponent->GetVelocity().x <= -EPSILON) m_spriteComponent->Play("run");
    else m_spriteComponent->Play("idle");
    if (m_physicsComponent->GetVelocity().x < -EPSILON)      m_spriteComponent->SetFlipH();
    else if (m_physicsComponent->GetVelocity().x > EPSILON) m_spriteComponent->SetFlipH(false);

    //std::cout << m_spriteComponent->GetCurrentAnimationName() << "\n";
    //std::cout << m_physicsComponent->GetVelocity().y << "\n";

    m_spriteComponent->Draw(renderer);
}

void PlatformerPlayer::OnCollision(Actor* actor)
{
    std::cout << actor->GetName();
    if (actor->HasTag("DamagesPlayer")) Destroy();
    if (actor->HasTag("Bouncer")) m_jump = 10000.f;
}
