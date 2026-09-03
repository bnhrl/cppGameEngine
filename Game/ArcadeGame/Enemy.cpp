#include "Enemy.h"
#include "Engine.h"

#include "Components/PhysicsComponent.h"

FACTORY_REGISTER(Enemy)

void Enemy::Update(float delta)
{
	if (destroyed) return;

	if (m_target != nullptr) {

		auto physicsComponent = GetComponent<PhysicsComponent>();
		if (physicsComponent) {
			Vector2 direction = m_transform.position.DirectionTo(m_target->GetTransform().position);
			float thrust = direction.Length() * m_speed;
			//float rotate = 0.f;
			physicsComponent->SetRotation(-direction.Angle());

			Vector2 forward{ 0,-1 };
			Vector2 force = forward.Rotate(m_transform.rotation) * thrust;

			physicsComponent->ApplyForce(force);
			//physicsComponent->ApplyTorque(rotate * delta);
		}
	}

	Actor::Update(delta);
}

void Enemy::Draw(const class Renderer& renderer) {
	Actor::Draw(renderer);
}

void Enemy::OnCollision(Actor* actor)
{
	if (destroyed) { return; }

	if (actor->HasTag("DamagesEnemy") || actor->HasTag("DamagesEverything"))
	{
		for (int i = 0; i < 10; i++)
		{
			Particle particle{ true, 1.0f, m_transform.position, Vector2(Random::Float(-1, 1) * 600.f, Random::Float(-1, 1) * 400.f), Color(1.f, 1.f, 1.f)};
			Engine::Get().GetPS().AddParticle(particle);
		}
		Engine::Get().GetAudio().PlaySound("enemy_death");
		Destroy();
	}
}
