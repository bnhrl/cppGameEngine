#include "pch.h"
#include "PowerUp.h"

#include "Core/Factory.h"

using namespace bnhe;

FACTORY_REGISTER(PowerUp)

void PowerUp::Update(float delta) {
    if (destroyed) return;

    m_transform.position += (m_velocity * delta);
}

void PowerUp::OnCollision(Actor* actor)
{
    if (destroyed) return;

    if (actor->HasTag("Player")) Destroy();
}

