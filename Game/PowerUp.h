#pragma once

#include "Actor.h"

using namespace bnhe;

class PowerUp : public Actor {
public:
	PowerUp(const Transform& transform, const Model& model, std::string type) : Actor{ transform, model } { AddTag("PowerUp"+type); }

	virtual void Update(float delta) override;
	virtual void OnCollision(Actor* actor) override;
};