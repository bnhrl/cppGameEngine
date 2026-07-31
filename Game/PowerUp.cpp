#include "pch.h"
#include "PowerUp.h"

using namespace bnhe;

void PowerUp::Update(float delta) {
    if (destroyed) return;

    m_transform.position += (m_velocity * delta);
}

void PowerUp::OnCollision(Actor* actor)
{
    if (destroyed) return;

    if (actor->HasTag("Player")) Destroy();
}

