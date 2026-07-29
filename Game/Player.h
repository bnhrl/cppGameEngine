#pragma once
#include "Actor.h"

#include "Models.h"

using namespace bnhe;

class Player : public Actor {
public:
	Player() = default;
	Player(const Transform& transform) : m_speed{ 500 }, Actor{ transform, Models::PlayerModel() } {
		AddTag("Player"); 
		m_effect_transform = transform;
		m_effect_model = Models::PlayerModel();
		SetSoulMode(ORANGE);
	}

	virtual void Update(float delta) override;
	virtual void Draw(const class Renderer& renderer) const;

	virtual void OnCollision(Actor* actor);

	enum SoulMode {RED, ORANGE, YELLOW};
	void SetSoulMode(SoulMode mode);

private:
	int m_ammo = 0;
	float m_speed = 10.0f;
	Model m_effect_model;
	Transform m_effect_transform;
	bool m_effect_growing = true;
};