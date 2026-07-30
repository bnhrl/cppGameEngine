#include "Player.h"

void Player::Update(float delta) {
    // Input
    Vector2 force = Vector2(0, 0);

    if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_UP)) force.y = -m_speed;
    if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_LEFT)) force.x = -m_speed;
    if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_DOWN)) force.y = +m_speed;
    if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_RIGHT)) force.x = +m_speed;

    if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_X)) force *= 0.5f;

    // Soul Modes

    if (m_sm_time_left <= 0.f && m_soulmode != RED) {
        SetSoulMode(RED);
    } else m_sm_time_left -= delta;

    switch (m_soulmode) {
        case RED:
            break;
        case YELLOW: // TODO add shooting
            if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_Z)) { // Charge Shot
                if ((int)(m_charge * 100) % 13 == 0 && m_charge < .5f) Engine::Get().GetAudio().PlaySound("player_charge");
                m_charge += delta;
            }
            else if (Engine::Get().GetInput().GetKeyReleased(SDL_SCANCODE_Z)) {
                if (m_charge >= .5f) {
                    // Big Shot
                }
                else {
                    // Normal Shot
                }
            }
            break;
        case ORANGE:
            if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_Z)) { // Charge Dash
                if ((int)(m_charge * 100) % 13 == 0 && m_charge < .5f) Engine::Get().GetAudio().PlaySound("player_charge");
                m_charge += delta;
            }
            else if (Engine::Get().GetInput().GetKeyReleased(SDL_SCANCODE_Z) && m_charge >= .5f) { // Dashing
                Engine::Get().GetAudio().PlaySound("player_dash");
                m_dash_force += m_dir * 6000;
                m_charge = 0.f;
            }
            else m_charge = 0.f;
            break;
    }
    // Charge effect
    if (m_charge > 0.f) {
        m_charge_transform.position = m_transform.position;
        m_charge_transform.rotation = m_transform.rotation;
        m_charge_transform.scale = m_transform.scale * math::Clamp(0.5 - m_charge, 0.0, 0.5) * 3.f + m_transform.scale;
    }
    // Damaging when dashing
    if (m_dash_force.Length() > 1.0f) {
        if (!HasTag("DamagesEnemy")) AddTag("DamagesEnemy");
    }
    else {
        RemoveTag("DamagesEnemy");
    }

    // Movement
    if (m_soulmode != RED) SetRotation(m_dir.Angle() + math::PI);
    else SetRotation(math::PI);
    SetVelocity(force);
    m_transform.position += m_velocity * delta;
    m_transform.position += m_dash_force * delta;
    SetVelocity(Vector2(0.0f));
    m_dash_force = m_dash_force.Lerp(Vector2(0.f), 24.f, delta);


    // Rotation
    if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_C)) m_dir.x *= -1;

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
    if (m_charge > 0.f) renderer.DrawModel(m_model, m_charge_transform);
    m_hp_text->Draw(Engine::Get().GetRenderer(), renderer.GetWidth() * 0.45f, renderer.GetHeight() - 96);
}

void Player::OnCollision(Actor* actor) {
    if (m_invincibility_time > 0.0f) return;

    if (actor->HasTag("DamagesPlayer") && !HasTag("DamagesEnemy")) {
        Engine::Get().GetAudio().PlaySound("player_hurt");
        Damage();
        std::cout << "Player hit! Health remaining: " << m_health << "\n";
    }
}


void Player::SetSoulMode(SoulMode mode)
{
    m_soulmode = mode;
    std::cout << "SWAPPING SOUL MODE TO " << mode << "\n";
    switch (m_soulmode)
    {
        case ORANGE:
            m_color = (Color(1.f, .5f, 0.f));
            break;
        case YELLOW:
            m_color = (Color(1.f, 1.f, 0.f));
            break;
        default:
            m_color = (Color(1.f, 0.f, 0.f));
            break;
    }
}
