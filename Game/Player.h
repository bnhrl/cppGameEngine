#pragma once
#include "Actor.h"

#include "Models.h"
#include "Engine.h"

using namespace bnhe;

class Player : public Actor {
public:
	Player() = default;
	Player(const Transform& transform) : m_speed{ 500 }, Actor{ transform, Models::PlayerModel() } {
		AddTag("Player"); 

		m_effect_transform = transform;
		m_effect_model = Models::PlayerModel();

		SetSoulMode(ORANGE);

		m_hp_text = new Text(Engine::Get().GetFont());
		UpdateHPText();
	}

	virtual void Update(float delta) override;
	virtual void Draw(const class Renderer& renderer) const;

	virtual void OnCollision(Actor* actor);

	enum SoulMode {RED, ORANGE, YELLOW};
	void SetSoulMode(SoulMode mode);

	void Damage() 
	{ 
		m_health -= 4; 
		m_invincibility_time += 1.25f; 

		if (m_health > 20) m_health = 20;
		else if (m_health < 0) m_health = 0;

		UpdateHPText(); 
	}
	void Heal() { 
		m_health += 4; 

		if (m_health > 20) m_health = 20;
		else if (m_health < 0) m_health = 0;

		UpdateHPText(); 
	}

private:
	// Stats
	int m_health = 20;
	float m_invincibility_time = 0.0f;
	float m_speed = 10.0f;
	Vector2 m_dir = Vector2(1.f, 0.f);
	SoulMode m_soulmode = RED;
	float m_sm_time_left = 0.f;
	Vector2 m_dash_force = Vector2(0.f);
	float m_charge = 0.f;

	// Visuals
	Color m_color = Color(1.f, 0.f, 0.f, 1.f);
	Text* m_hp_text;
	void UpdateHPText() { m_hp_text->Create(Engine::Get().GetRenderer(), std::to_string(m_health) + " / 20", Color{ 1, 1, 1, 1 }); }

	// Effects
	Model m_effect_model;
	Transform m_effect_transform;
	bool m_effect_growing = true;
	Transform m_charge_transform;
};