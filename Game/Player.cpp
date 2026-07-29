#include "Player.h"
#include "Engine.h"

void Player::Update(float delta) {
    Vector2 force = Vector2(0, 0);

    if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_UP)) force.y = -m_speed;
    if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_LEFT)) force.x = -m_speed;
    if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_DOWN)) force.y = +m_speed;
    if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_RIGHT)) force.x = +m_speed;

    SetVelocity(force);
    m_transform.position += (m_velocity * delta);
    SetVelocity(Vector2(0.0f));

    m_effect_transform.position = GetTransform().position;
    m_effect_transform.rotation = GetTransform().rotation;
    if (m_effect_growing)
        m_effect_transform.scale = m_effect_transform.scale.Lerp(Vector2(5.f), 4.f, delta);
    else
        m_effect_transform.scale = m_effect_transform.scale.Lerp(Vector2(3.f), 4.f, delta);

    if (m_effect_transform.scale.x >= 4.9f)      m_effect_growing = false;
    else if (m_effect_transform.scale.x <= 3.1f) m_effect_growing = true;
}

void Player::Draw(const class Renderer& renderer) const {
    Actor::Draw(renderer);
    renderer.DrawModel(m_model, m_effect_transform);
}

void Player::OnCollision(Actor* actor) {
    std::cout << actor->GetTransform().rotation << "\n";
}


void Player::SetSoulMode(SoulMode mode)
{
    std::cout << "SWAPPING SOUL MODE TO " << mode << "\n";
    switch (mode) 
    {
        case ORANGE:
            m_model.SetMeshColor(Color(1.f, .5f, 0.f));
            m_effect_model.SetMeshColor(Color(.75f, .25f, 0.f));
            m_transform.rotation = -math::PI;
            break;
        case YELLOW:
            m_model.SetMeshColor(Color(1.f, 1.f, 0.f));
            m_effect_model.SetMeshColor(Color(.75f, .75f, 0.f));
            m_transform.rotation = -math::PI;
            break;
        default:
            m_model.SetMeshColor(Color(1.f, 0.f, 0.f));
            m_effect_model.SetMeshColor(Color(.75f, 0.f, 0.f));
            m_transform.rotation = 0.0f;
            break;
    }
}
