#pragma once

#include "Actor.h"

using namespace bnhe;

class PowerUp : public Actor {
public:
	PowerUp(const Transform& transform, const res_t<Texture> texture, std::string type) : Actor{ transform, texture } { AddTag("PowerUp"+type); }

	virtual void Update(float delta) override;
	virtual void OnCollision(Actor* actor) override;
};