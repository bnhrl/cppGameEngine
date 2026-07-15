#pragma once

#include "Actor.h"

using namespace bnhe;

class Player : Actor {
public:
	Player() = default;
	Player(float speed, const Transform& transform, const Model& model) : m_speed{ speed }, Actor { transform, model } {}

	virtual void Update(float delta) override;

	virtual void Draw(const class Renderer& renderer) const;

private:
	int m_ammo = 0;
	float m_speed;
};