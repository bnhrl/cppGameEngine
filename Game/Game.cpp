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

    // Scenes
    float points = 0.f;
    // Menu scene
    Scene* menuScene = new Scene("Menu");
    Text* textTitle = new Text(engine.GetFontBig()); textTitle->Create(engine.GetRenderer(), "UNNAMED C++ GAME", Color{ 1, 1, 1, 1 });
    Text* textInstructions = new Text(engine.GetFont()); 
    textInstructions->Create(engine.GetRenderer(),
        "[ARROW KEYS] to MOVE. [X] to MOVE SLOWER." 
        "                                              "
        "Press [Z] to attack when you have a POWER-UP."
        "                                              "
        "Press [C] to FLIP."
        "                                              "
        "SURVIVE or DEFEAT ENEMIES to gain POINTs."
        "                                              "
        "Press [Z] to START!",
        Color{ 1, 1, 1, 1 }, 720);
    Text* textCredits = new Text(engine.GetFont()); textCredits->Create(engine.GetRenderer(), "[heavily inspired by UNDERTALE/deltarune]", Color{ 1, 1, 1, 1 });
    // Game scene
    Scene* gameScene = new Scene("Game");
    Text* textPoints = new Text(engine.GetFont()); textTitle->Create(engine.GetRenderer(), "0 POINTs", Color{ 1, 1, 1, 1 });
    // Death scene
    Scene* deathScene = new Scene("Death");
    // Adding scenes to SceneManager
    engine.GetSM().AddScene(menuScene);
    engine.GetSM().AddScene(gameScene);
    engine.GetSM().AddScene(deathScene);
    engine.GetSM().SetActiveScene("Menu");


    // Player
    Transform pTransform = Transform(Vector2(RESOLUTION_X / 2.0f, RESOLUTION_Y / 2.0f), 0.0f, Vector2(4.0f));
    Player player{ pTransform};
    gameScene->AddActor(&player);

    // Enemies
    std::vector<Enemy*> enemies;
    for (int i = 0; i < 10; i++) {
        Transform enemyTransform{ Random::PointOnScreen(), 0.0f, Vector2(4.0f) };
        Enemy* enemy = new Enemy(enemyTransform, Models::PlayerModel());
        enemy->SetTarget(&player);
        gameScene->AddActor(enemy);
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
        // Scenes
        ///
        if (engine.GetSM().GetActiveScene() == menuScene) 
        {
            textTitle->Draw(engine.GetRenderer(), 32, 32);
            textInstructions->Draw(engine.GetRenderer(), 32, 160);
            textCredits->Draw(engine.GetRenderer(), 32, RESOLUTION_Y - 82);
            if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_Z)) engine.GetSM().SetActiveScene("Game");
        }
        else if (engine.GetSM().GetActiveScene() == gameScene) {
            points += engine.GetTime().GetDeltaTime();
            textPoints->Create(engine.GetRenderer(), std::to_string((int)points) + " POINTs", Color{ 1, 1, 1, 1 });
            textPoints->Draw(engine.GetRenderer(), RESOLUTION_Xf * 0.45f, 16);

            for (auto enemy : enemies) {
                if (enemy->IsDestroyed()) {
                    //TODO: respawning enemies
                }
            }
        }



        ///
        // Engine
        ///

        engine.Update();
        float delta = engine.GetTime().GetDeltaTime();



        ///
        // Render
        ///

        engine.GetSM().GetActiveScene()->Draw(engine.GetRenderer());
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
