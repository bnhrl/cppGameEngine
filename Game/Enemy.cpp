#include "Enemy.h"
#include "Engine.h"

FACTORY_REGISTER(Enemy)

void Enemy::Update(float delta)
{
	if (destroyed) return;

	if (m_target != nullptr) {
		Vector2 force = Vector2(0, 0);
		force = m_transform.position.DirectionTo(m_target->GetTransform().position) * -m_speed;
		SetVelocity(GetVelocity() + force * delta);

		//float targetRot = m_transform.position.AngleTo(m_target->GetTransform().position);
		//SetRotation(targetRot);
	}

	Actor::Update(delta);
}

void Enemy::Draw(const class Renderer& renderer) const {
	Actor::Draw(renderer);
}

void Enemy::OnCollision(Actor* actor)
{
	if (destroyed) { return; }

	if (actor->HasTag("DamagesEnemy") || actor->HasTag("DamagesEverything"))
	{
		/*if (m_texture) {
			for (int i = 0; i < 10; i++)
			{
				Particle particle{ true, 1.0f, m_transform.position, Vector2(Random::Float(-1, 1) * 600.f, Random::Float(-1, 1) * 400.f), Color(1.f, 1.f, 1.f)};
				Engine::Get().GetPS().AddParticle(particle);
			}
			Engine::Get().GetAudio().PlaySound("enemy_death");
			Destroy();
			return;
		}

		Color color = m_model.GetMeshes()[0].GetColor();
		for (int i = 0; i < 10; i++)
		{
			Particle particle{ true, 1.0f, m_transform.position, Vector2(Random::Float(-1, 1) * 600.f, Random::Float(-1, 1) * 400.f), color };
			Engine::Get().GetPS().AddParticle(particle);
		}
		Engine::Get().GetAudio().PlaySound("enemy_death"); */
		Destroy();
	}
}
