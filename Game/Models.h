#pragma once

#include <Model.h>
using namespace bnhe;

class Models {
public:
	static Model PlayerModel() {
		Mesh mesh0{ {Vector2(0,-2),Vector2(2,-5),Vector2(5,-3),Vector2(4,1),Vector2(0,4),Vector2(-4,1),Vector2(-5,-3),Vector2(-2,-5),Vector2(0,-2)}, Color(1.f, 1.f, 1.f) };

		Model model = Model({ mesh0 });
		return model;
	}

	/*Model BossModel() {

	}*/
};