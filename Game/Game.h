#pragma once
#include "Engine.h"

class Game {
public:
	Game() = default;
	~Game() = default;

	virtual int Run() { return 0; }

	const int RESOLUTION_X = 1280;
	const int RESOLUTION_Y = 960;
	const float RESOLUTION_Xf = RESOLUTION_X;
	const float RESOLUTION_Yf = RESOLUTION_Y;


};