#pragma once

#include "Actor.h"

using namespace bnhe;

class Enemy : public bnhe::Actor {
public:
	Enemy() = default;
	Enemy(const Transform& transform, const Model& model) : Actor{ transform, model } {}

	virtual void Update(float delta) override;
	virtual void Draw(const class Renderer& renderer) const;

	void SetTarget(Actor* actor) { m_target = actor; }

protected:
	Actor* m_target = nullptr;
	float m_speed = 3000.0f;
};