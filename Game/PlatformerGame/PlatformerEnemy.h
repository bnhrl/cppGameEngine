#pragma once
#include "Framework/Actor.h"

#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorRendererComponent.h"

using namespace bnhe;

class PlatformerEnemy : public Actor
{
public:
	CLASS_PROTOTYPE(PlatformerEnemy);

	PlatformerEnemy() = default;

	virtual void OnStart() override;
	virtual void Update(float delta) override;

	virtual void OnCollision(Actor* actor) override;

	void SetTarget(Actor* target) { m_target = target; }

protected:
	PhysicsComponent* m_physicsComponent = nullptr;
	SpriteAnimatorRendererComponent* m_spriteComponent = nullptr;
	Actor* m_target = nullptr;
	float m_speed = 50.f;
	float m_jump = 0.f;
};