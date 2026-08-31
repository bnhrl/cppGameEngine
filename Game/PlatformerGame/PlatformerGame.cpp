#include "pch.h"
#include "PlatformerGame.h"

int PlatformerGame::Run() 
{
    ///
    // INITIALIZATION
    ///

    SetWorkingDirectory("PlatformerGame/Assets");
    Engine& engine = Engine::Get();
    engine.Initialize(RESOLUTION_X, RESOLUTION_Y);

    return 0;
}