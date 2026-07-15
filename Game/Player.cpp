#include "Player.h"
#include "Engine.h"

void Player::Update(float delta) {
    float speed = 2000.0f;
    
    Vector2 force = Vector2(0, 0);

    if (engine.GetInput().GetKeyDown(SDL_SCANCODE_W)) force.y = -speed;
    if (engine.GetInput().GetKeyDown(SDL_SCANCODE_A)) force.x = -speed;
    if (engine.GetInput().GetKeyDown(SDL_SCANCODE_S)) force.y = +speed;
    if (engine.GetInput().GetKeyDown(SDL_SCANCODE_D)) force.x = +speed;

    SetVelocity(GetVelocity() + force * engine.GetTime().GetDeltaTime());
    SetRotation(GetTransform().rotation + delta);

    Actor::Update(delta);
}

void Player::Draw(const class Renderer& renderer) const {
    Actor::Draw(renderer);
}