#include "Player.h"
#include "Engine.h"

void Player::Update(float delta) {
    // Input
    Vector2 force = Vector2(0, 0);

    if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_UP)) force.y = -m_speed;
    if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_LEFT)) force.x = -m_speed;
    if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_DOWN)) force.y = +m_speed;
    if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_RIGHT)) force.x = +m_speed;

    SetVelocity(force);
    m_transform.position += (m_velocity * delta);
    SetVelocity(Vector2(0.0f));

    // Effect
    m_effect_transform.position = GetTransform().position;
    m_effect_transform.rotation = GetTransform().rotation;
    if (m_effect_growing)
        m_effect_transform.scale = m_effect_transform.scale.Lerp(Vector2(5.f), 4.f, delta);
    else
        m_effect_transform.scale = m_effect_transform.scale.Lerp(Vector2(3.f), 4.f, delta);

    if (m_effect_transform.scale.x >= 4.9f)      m_effect_growing = false;
    else if (m_effect_transform.scale.x <= 3.1f) m_effect_growing = true;

    // Invincibility frames
    if (m_invincibility_time > 0.f) {
        m_invincibility_time -= delta;
        // Flashing
        Color color = m_color - sin(m_invincibility_time * 24.f) * 2.f;
        m_model.SetMeshColor(color);
    }
    else {
        m_model.SetMeshColor(m_color);
    }
    m_effect_model.SetMeshColor(m_color * 0.75f);
}

void Player::Draw(const class Renderer& renderer) const {
    renderer.DrawModel(m_effect_model, m_effect_transform);
    Actor::Draw(renderer);
}

void Player::OnCollision(Actor* actor) {
    if (m_invincibility_time > 0.0f) return;

    if (actor->HasTag("DamagesPlayer")) {
        m_invincibility_time += 1.25f;
        m_health -= 4;
        std::cout << "Player hit! Health remaining: " << m_health << "\n";
        for (int i = 0; i < 100; i++) 
        {
            Particle particle{ true, 2.0f, m_transform.position, Vector2(Random::Float(-1, 1) * 400.f, Random::Float(-1, 1) * 400.f), m_color };
            Engine::Get().GetPS().AddParticle(particle);
        }
    }
}


void Player::SetSoulMode(SoulMode mode)
{
    std::cout << "SWAPPING SOUL MODE TO " << mode << "\n";
    switch (mode) 
    {
        case ORANGE:
            m_color = (Color(1.f, .5f, 0.f));
            m_transform.rotation = -math::PI;
            break;
        case YELLOW:
            m_color = (Color(1.f, 1.f, 0.f));
            m_transform.rotation = -math::PI;
            break;
        default:
            m_color = (Color(1.f, 0.f, 0.f));
            m_transform.rotation = 0.0f;
            break;
    }
}
