#pragma once

#include "Engine.h"

using namespace bnhe;

class Bullet : public Actor
{
public:
	Bullet(const Transform& transform, std::string damagesTag, Vector2 direction, float speed, Color color, int pierces = 2) : Actor{transform, Resources().Get<Texture>("Textures/bullet.png", Engine::Get().GetRenderer()) }
	{ 
		m_pierces = pierces;
		AddTag("Damages"+damagesTag);
		SetVelocity(direction * speed);
		m_modulate = color;
	}

	virtual void Update(float delta) override;

	virtual void OnCollision(Actor* actor) override;

private:
	int m_pierces;
};