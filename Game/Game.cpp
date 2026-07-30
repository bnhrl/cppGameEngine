#include <iostream>
#include <vector>
#include <map>

#include <SDL3/SDL.h>
#include <fmod.hpp>

#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Models.h"

const int RESOLUTION_X = 1280;
const int RESOLUTION_Y = 960;
const float RESOLUTION_Xf = RESOLUTION_X;
const float RESOLUTION_Yf = RESOLUTION_Y;

using namespace bnhe;


int main()
{
    ///
    // INITIALIZATION
    ///

    Engine& engine = Engine::Get();
    engine.Initialize(RESOLUTION_X, RESOLUTION_Y);

    //Text* text = new Text(engine.GetFont());
    //text->Create(engine.GetRenderer(), "20 / 20", Color{ 1, 1, 1, 1 });



    ///
    // Values
    ///

    // Scene
    Scene scene = Scene();


    // Player
    Transform pTransform = Transform(Vector2(RESOLUTION_X / 2.0f, RESOLUTION_Y / 2.0f), 0.0f, Vector2(4.0f));
    Player player{ pTransform};
    scene.AddActor(&player);

    // Enemies
    std::vector<Enemy*> enemies;
    for (int i = 0; i < 10; i++) {
        Transform enemyTransform{ Random::PointOnScreen(), 0.0f, Vector2(4.0f) };
        Enemy* enemy = new Enemy(enemyTransform, Models::PlayerModel());
        enemy->SetTarget(&player);
        scene.AddActor(enemy);
        enemies.push_back(enemy);
    }

    // Drawing
    Color backgroundColor = Color(0, 0, 0);



    ///
    // MAIN LOOP
    ///
    SDL_Event e;
    bool quit = false;

    while (!quit) {
        ///
        // UPDATE
        ///

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }



        ///
        // Engine
        ///

        engine.Update();
        float delta = engine.GetTime().GetDeltaTime();
        scene.Update(delta);
        scene.UpdateCollisions();



        ///
        // Render
        ///

        scene.Draw(engine.GetRenderer());
        engine.GetPS().Draw(engine.GetRenderer());
        engine.GetRenderer().Present(); // Render the screen

        engine.GetRenderer().SetColor(backgroundColor); // Set render draw color to black
        engine.GetRenderer().Clear();                // Clear the renderer
        engine.UpdateAudio();
    }



    ///
    // SHUTDOWN
    ///

    engine.Shutdown();

    return 0;
}
