#include "Player.h"
#include "Bullet.h"

#include "Components/PhysicsComponent.h"

FACTORY_REGISTER(Player)

void Player::Read(const json::value_t& value) {
    Actor::Read(value);
    if (JSON_HAS_NAME(value, "speed")) JSON_READ_NAME(value, "speed", m_speed);
}

void Player::Update(float delta) {
    for (auto& component : m_components) {
        component->Update(delta);
    }

    // Input
    float thrust = 0.f;
    if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_UP)) thrust = m_speed;
    else if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_DOWN)) thrust = -m_speed;
    float rotate = 0.f;
    if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_LEFT)) rotate = -32.0;
    if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_RIGHT)) rotate = 32.0;


    // Soul Modes
    if (m_sm_time_left <= 0.f && m_soulmode != RED) {
        SetSoulMode(RED);
    } else if (m_sm_time_left > 0.f) m_sm_time_left -= delta;

    switch (m_soulmode) {
        case RED:
            m_charge = 0.f;
            break;
        case YELLOW:
            if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_Z)) { // Charge Shot
                if ((int)(m_charge * 100) % 13 == 0 && m_charge < .5f) Engine::Get().GetAudio().PlaySound("player_charge");
                m_charge += delta;
            }
            else if (Engine::Get().GetInput().GetKeyReleased(SDL_SCANCODE_Z)) { 
                if (m_charge >= .5f) { // Big Shot
                    Engine::Get().GetAudio().PlaySound("player_shoot_big");
                    Transform transform{ m_transform.position, 0.f, Vector2(.75f) };
                    auto bullet = bnhe::Factory().Instance().Create<Bullet>("BulletPrototype");

                    bullet->AddTag("DamagesEnemy");
                    bullet->SetTransform(transform);
                    m_scene->AddActor(std::move(bullet));

                    m_charge = 0.f;
                }
                else { // Normal Shot
                    Engine::Get().GetAudio().PlaySound("player_shoot");
                    Transform transform{ m_transform.position, 0.f, Vector2(.33f) };
                    auto bullet = bnhe::Factory().Instance().Create<Bullet>("BulletPrototype");

                    bullet->AddTag("DamagesEnemy");
                    bullet->SetTransform(transform);
                    m_scene->AddActor(std::move(bullet));

                    m_charge = 0.f;
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
        m_charge_transform.scale = m_transform.scale * (float)math::Clamp(0.5 - m_charge, 0.0, 0.5) * 3.f + m_transform.scale;
    }
    // Damaging when dashing
    if (m_dash_force.Length() > 1.0f) {
        if (!HasTag("DamagesEnemy")) AddTag("DamagesEnemy");
    }
    else {
        RemoveTag("DamagesEnemy");
    }

    // Movement
    auto physicsComponent = GetComponent<PhysicsComponent>();
    if (physicsComponent) {
        Vector2 forward{ 0,-1 };
        Vector2 force = forward.Rotate(m_transform.rotation) * thrust;

        physicsComponent->ApplyForce(force);
        physicsComponent->ApplyTorque(rotate * delta);
    }

    //if (m_soulmode != RED) SetRotation(m_dir.Angle() + math::PI);
    //else SetRotation(math::PI*2.0);
    //SetVelocity(force);
    //m_transform.position += m_velocity * delta;
    //m_transform.position += m_dash_force * delta;
    //SetVelocity(Vector2(0.0f));
    //m_dash_force = m_dash_force.Lerp(Vector2(0.f), 24.f, delta);
    if (m_transform.position.x < 0.f) m_transform.position.x = 0.f;
    else if (m_transform.position.x > (float)Engine::Get().GetRenderer().GetWidth()) m_transform.position.x = (float)Engine::Get().GetRenderer().GetWidth();
    if (m_transform.position.y < 0.f) m_transform.position.y = 0.f;
    else if (m_transform.position.y > (float)Engine::Get().GetRenderer().GetHeight()) m_transform.position.y = (float)Engine::Get().GetRenderer().GetHeight();

    //// Rotation
    //if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_C)) m_dir.x *= -1;

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
        Color color = Color(m_color.r, m_color.g, m_color.b, m_color.a - sin(m_invincibility_time * 12.f) * 1.f);
        m_modulate = (color);
    }
    else {
        m_modulate = m_color;
    }
}

void Player::Draw(const class Renderer& renderer) {
    Actor::Draw(renderer);
    if (m_charge > 0.1f) {
        Color color = m_modulate;
        color.a -= 0.5;
    }

    m_hp_text->Draw(renderer, renderer.GetWidth() * 0.45f, (float)renderer.GetHeight() - 96);
}

void Player::OnCollision(Actor* actor) {

    if ((actor->HasTag("DamagesPlayer") && !this->HasTag("DamagesEnemy")) || (actor->HasTag("DamagesEverything"))) {
        if (m_invincibility_time > 0.0f) return;

        Damage();
        std::cout << "Player hit! Health remaining: " << m_health << "\n";
    }

    if (actor->HasTag("PowerUpYellow")) {
        Heal();
        SetSoulMode(YELLOW);
        actor->Destroy();
    }
    else if (actor->HasTag("PowerUpOrange")) {
        Heal();
        SetSoulMode(ORANGE);
        actor->Destroy();
    }
}


void Player::SetSoulMode(SoulMode mode)
{
    m_soulmode = mode;
    std::cout << "SWAPPING SOUL MODE TO " << mode << "\n";
    switch (m_soulmode)
    {
        case ORANGE:
            m_sm_time_left = 10.f;
            m_color = (Color(1.f, .5f, 0.f));
            break;
        case YELLOW:
            m_sm_time_left = 7.5f;
            m_color = (Color(1.f, 1.f, 0.f));
            break;
        default:
            m_color = (Color(1.f, 0.f, 0.f));
            break;
    }
}
