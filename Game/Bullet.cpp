#include "pch.h"
#include "Bullet.h"

#include "Renderer/Renderer.h"

FACTORY_REGISTER(Bullet)

void Bullet::Update(float delta)
{
    if (destroyed) return;

    m_transform.position += (m_velocity * delta);

    if (m_transform.position.x < -16.f || m_transform.position.x > Renderer::GetWidth() + 16.f) { Destroy(); }
    else if (m_transform.position.y < -16.f || m_transform.position.y > Renderer::GetHeight() + 16.f) { Destroy(); }
}

void Bullet::OnCollision(Actor* actor)
{
	if ((actor->HasTag("Player") && HasTag("DamagesPlayer")) || (actor->HasTag("Enemy") && HasTag("DamagesEnemy"))) {
		m_pierces -= 1;

		if (m_pierces <= 0) Destroy();
	}
}
