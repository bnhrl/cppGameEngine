#pragma once

#include "Framework/Actor.h"
#include "Math/Random.h"

using namespace bnhe;

class Enemy : public bnhe::Actor {
public:
	CLASS_PROTOTYPE(Enemy)

	Enemy() = default;
	Enemy(const Transform& transform, const res_t<Texture> texture) : Actor{ transform, texture } { AddTag("DamagesPlayer"); AddTag("Enemy"); m_speed = Random::Float(2000.f, 3150.f); }

	virtual void Update(float delta) override;
	virtual void Draw(const class Renderer& renderer) const override;

	void SetTarget(Actor* actor) { m_target = actor; }
	virtual void OnCollision(Actor* actor) override;

protected:
	Actor* m_target = nullptr;
	float m_speed = 3000.0f;
};