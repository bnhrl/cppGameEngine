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

void Player::SetSoulMode(SoulMode mode)
{
    switch (mode) {
    case RED:
        m_model.GetMeshes()
        break;
    case YELLOW:
        break;
    case ORANGE:
        break;
    }
}
