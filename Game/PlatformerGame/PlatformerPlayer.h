#pragma once
#include "Framework/Actor.h"

#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorRendererComponent.h"

using namespace bnhe;

class PlatformerPlayer : public Actor {
public:
	CLASS_PROTOTYPE(PlatformerPlayer)

	PlatformerPlayer() = default;

	void OnStart() override;
	void Update(float delta) override;
	void Draw(const class Renderer& renderer) override;

	void OnCollision(Actor* actor) override;

protected:
	PhysicsComponent* m_physicsComponent = nullptr;
	SpriteAnimatorRendererComponent* m_spriteComponent = nullptr;

private:
	float m_speed = 300.0f;
	float m_invincibility = 0.f;
	float m_jump = 0.f;
};