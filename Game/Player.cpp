#include "Player.h"
#include "Engine.h"

void Player::Update(float delta) {
    Vector2 force = Vector2(0, 0);

    if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)) force.y = -m_speed;
    if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) force.x = -m_speed;
    if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_S)) force.y = +m_speed;
    if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) force.x = +m_speed;

    SetVelocity(GetVelocity() + force * delta);

    float targetRot = GetTransform().position.AngleTo(Engine::Get().GetInput().GetMousePosition());
    SetRotation(targetRot);

    Actor::Update(delta);
}

void Player::Draw(const class Renderer& renderer) const {
    Actor::Draw(renderer);
}