#include <iostream>
#include <vector>
#include <map>

#include <SDL3/SDL.h>
#include <fmod.hpp>

#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Models.h"

const int RESOLUTION_X = 640;
const int RESOLUTION_Y = 480;
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

    Font* font = new Font();
    font->Load("Pixelzone.ttf", 96);

    Text* text = new Text(font);
    text->Create(engine.GetRenderer(), "Hello World", Color{ 1, 1, 1, 1 });



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
    Transform enemyTransform{ Random::PointOnScreen(), 0.0f, Vector2(16.0f) };
    Mesh enemyMesh0{ {Vector2(4,4),Vector2(-4,-4),Vector2(0,4)}, Color(1,0,0)};
    Mesh enemyMesh1{ {Vector2(4,-4),Vector2(-4,4),Vector2(0,-4)}, Color(1,0.5,0)};
    Model enemyModel{ {enemyMesh0,enemyMesh1} };
    std::vector<Enemy> enemies;
    // TODO Figure out how to put them in a for loop
    Enemy enemy{ enemyTransform, enemyModel };
    enemy.SetTarget(&player);
    scene.AddActor(&enemy);

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



        /// 
        // Input
        ///

        // Sounds
        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_1))
        {
            engine.GetAudio().PlaySound("test_0");
        }
        else if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_2))
        {
            engine.GetAudio().PlaySound("test_1");
        }
        else if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_3))
        {
            engine.GetAudio().PlaySound("test_2");
        }

        scene.Draw(engine.GetRenderer());
        text->Draw(engine.GetRenderer(), 128, 128);
        engine.GetRenderer().Present(); // Render the screen



        ///
        // Render
        ///

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
