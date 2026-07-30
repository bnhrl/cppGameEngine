#pragma once

#include <Model.h>
using namespace bnhe;

class Models {
public:
	static Model PlayerModel() {
		Mesh mesh0{ {Vector2(0,-2),Vector2(2,-5),Vector2(5,-3),Vector2(4,1),Vector2(0,4),Vector2(-4,1),Vector2(-5,-3),Vector2(-2,-5),Vector2(0,-2)}, Color(1.f, 1.f, 1.f) };
		return Model( {mesh0} );
	}

	static Model CloverModel() {
		Mesh mesh0{ {Vector2(-5,-2), Vector2(-3,-5), Vector2(0,0), Vector2(2,-5), Vector2(5, -3), Vector2(0, 0), Vector2(-5,2), Vector2(-3,5), Vector2(0,0), Vector2(2,5), Vector2(5, 3), Vector2(0, 0)}, Color(0.f, 1.f, 0.f)};
		return Model( {mesh0} );
	}

	static Model BulletMesh() {
		Mesh mesh0 { {Vector2{ -1, -1 }, Vector2{ 1, 0 }, Vector2{ -1, 1 }, Vector2{ -1, -1 }, }, Color{ 1.0f, 0.0f, 0.0f }};
		return Model{ {mesh0} };
	}

	/*static Model Model() {

	}*/
};