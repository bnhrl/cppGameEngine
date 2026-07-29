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
		SetSoulMode(RED);
	}

	virtual void Update(float delta) override;
	virtual void Draw(const class Renderer& renderer) const;

	virtual void OnCollision(Actor* actor);

	enum SoulMode {RED, ORANGE, YELLOW};
	void SetSoulMode(SoulMode mode);

private:
	// Stats
	int m_health = 20;
	float m_invincibility_time = 0.0f;
	float m_speed = 10.0f;

	// Visuals
	Color m_color = Color(1.f, 0.f, 0.f, 1.f);

	// Effects
	Model m_effect_model;
	Transform m_effect_transform;
	bool m_effect_growing = true;
};