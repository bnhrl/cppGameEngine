#pragma once

#include "Actor.h"
#include "Models.h"

using namespace bnhe;

class Bullet : public Actor
{
public:
	Bullet(const Transform& transform, std::string damagesTag, Vector2 direction, float speed, Color color, int pierces = 2) : Actor{transform, Models::BulletModel()}
	{ 
		m_pierces = pierces;
		AddTag("Damages"+damagesTag);
		SetVelocity(direction * speed);
		m_model.SetMeshColor(color);
	}

	virtual void Update(float delta) override;

	virtual void OnCollision(Actor* actor) override;

private:
	int m_pierces;
};