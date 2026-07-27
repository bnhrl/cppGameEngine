#include <iostream>
#include <vector>
#include <map>

#include <SDL3/SDL.h>
#include <fmod.hpp>

#include "Engine.h"
#include "Player.h"
#include "Enemy.h"

const int RESOLUTION_X = 1920;
const int RESOLUTION_Y = 1200;
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



    ///
    // Values
    ///

    // Scene
    Scene scene = Scene();


    // Player
    Transform pTransform = Transform(Vector2(RESOLUTION_X / 2.0f, RESOLUTION_Y / 2.0f), 0.0f, Vector2(16.0f));
    Mesh mesh0{ {Vector2(-4,0),Vector2(-2,-4),Vector2(0,-2),Vector2(1,-5),Vector2(2,5),Vector2(3,1),Vector2(7,0)}, Color(0.f, 1.f, 0.f) };
    Mesh mesh1{ {Vector2(-4,0),Vector2(-2,4),Vector2(0,2),Vector2(1,5),Vector2(2,-5),Vector2(3,-1),Vector2(7,0)}, Color(1.f, 0.f, 1.f) };
    Model model = { {mesh0, mesh1} };
    Player player{ 3000.0f, pTransform, model };
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

    // Test menu
    Vector2 menuPosOpen = Vector2(RESOLUTION_Xf / 2.0f, RESOLUTION_Yf / 2.0f);
    Vector2 menuPosClosed = Vector2(-RESOLUTION_Xf / 2.0f, RESOLUTION_Yf / 2.0f);
    Vector2 menuPos = menuPosClosed;
    bool menuOpen = false;



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

        // Test menu
        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_TAB)) menuOpen = !menuOpen;

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

        // Test Menu
        engine.GetRenderer().SetColor(0, 0, 1.f);
        if (menuOpen) { menuPos = menuPos.Lerp(menuPosOpen, 16.0f, delta); }
        else { menuPos = menuPos.Lerp(menuPosClosed, 16.0f, delta);; }
        engine.GetRenderer().DrawRect(menuPos, Vector2(1280, 640));

        scene.Draw(engine.GetRenderer());
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
