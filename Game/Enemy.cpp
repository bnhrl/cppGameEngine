#include "Enemy.h"
#include "Engine.h"

void Enemy::Update(float delta)
{
	if (m_target != nullptr) {
		Vector2 force = Vector2(0, 0);
		force = m_transform.position.DirectionTo(m_target->GetTransform().position) * -m_speed;
		SetVelocity(GetVelocity() + force * delta);

		SetRotation(m_transform.position.AngleTo(m_target->GetTransform().position));
	}

	Actor::Update(delta);
}

void Enemy::Draw(const class Renderer& renderer) const {
	Actor::Draw(renderer);
}
