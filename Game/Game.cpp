#include <iostream>
#include <vector>
#include <map>

#include <SDL3/SDL.h>
#include <fmod.hpp>

#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Models.h"
#include "PowerUp.h"
#include "Bullet.h"

const int RESOLUTION_X = 1280;
const int RESOLUTION_Y = 960;
const float RESOLUTION_Xf = RESOLUTION_X;
const float RESOLUTION_Yf = RESOLUTION_Y;

using namespace bnhe;



Enemy* CreateEnemy(Scene* scene, Player* player) {
    Transform transform;
    if (Random::Int(1)) transform = { Vector2(0, Random::PointOnScreen().y), 0.0f, Vector2(4.0f) };
    else                transform = { Vector2(RESOLUTION_X, Random::PointOnScreen().y), 0.0f, Vector2(4.0f) };
    Enemy* enemy = new Enemy(transform, Models::PlayerModel());
    enemy->SetTarget(player);
    scene->AddActor(enemy);
    return enemy;
}

Bullet* CreateBullet(Scene* scene) {
    Transform transform;
    Vector2 direction;
    if (Random::Int(1)) { transform = { Vector2(0, Random::PointOnScreen().y), 0.0f, Vector2(4.0f) }; direction = Vector2(1.f, 0.f); }
    else                { transform = { Vector2(RESOLUTION_X, Random::PointOnScreen().y), 0.0f, Vector2(4.0f) }; direction = Vector2(-1.f, 0.f); }
    Bullet* bullet = new Bullet(transform, "Everything", direction, 1200.f, Color(0.f, 1.f, 1.f), 3);
    scene->AddActor(bullet);
    return bullet;
}

PowerUp* CreatePowerUp(Scene* scene, Player* player) {
    PowerUp* powerUp = nullptr;
    Transform transform;
    if (Random::Int(1)) transform = { Vector2(0, Random::PointOnScreen().y), 0.0f, Vector2(4.0f) };
    else                transform = { Vector2(RESOLUTION_X, Random::PointOnScreen().y), 0.0f, Vector2(4.0f) };
    Player::SoulMode type = (Player::SoulMode)Random::Int(1, 2);
    if (type == Player::YELLOW)
        powerUp = new PowerUp(transform, Models::CloverModel(), "Yellow");
    else
        powerUp = new PowerUp(transform, Models::ThumbsModel(), "Orange");
    powerUp->SetVelocity(transform.position.DirectionTo(player->GetTransform().position) * -200.f);
    scene->AddActor(powerUp);
    return powerUp;
}

Player* CreatePlayer(Scene* scene) {
    Transform pTransform = Transform(Vector2(RESOLUTION_X / 2.0f, RESOLUTION_Y / 2.0f), 0.0f, Vector2(4.0f));
    Player* player = new Player(pTransform);
    scene->AddActor(player);
    return player;
}

float points = 0.f;
const float MAX_TIME_UNTIL_ENEMY        = 5.f;
const float MAX_TIME_UNTIL_BULLET       = 5.f;
const float MAX_TIME_UNTIL_POWER_UP     = 8.f;
float MAX_timeUntilEnemy                = MAX_TIME_UNTIL_ENEMY;
float MAX_timeUntilBullet               = MAX_TIME_UNTIL_BULLET;
float MAX_timeUntilPowerUp              = MAX_TIME_UNTIL_POWER_UP;
float timeUntilEnemy                    = MAX_timeUntilEnemy;
float timeUntilBullet                   = MAX_timeUntilBullet;
float timeUntilPowerUp                  = MAX_timeUntilPowerUp;


void StartGame(Scene* scene, Player*& player) {
    scene->Clear(); // Cleaning up scene

    // Resetting Values
    points = 0.f;
    MAX_timeUntilEnemy = MAX_TIME_UNTIL_ENEMY;
    MAX_timeUntilBullet = MAX_TIME_UNTIL_BULLET;
    MAX_timeUntilPowerUp = MAX_TIME_UNTIL_POWER_UP;
    timeUntilEnemy = MAX_timeUntilEnemy;
    timeUntilBullet = MAX_timeUntilBullet;
    timeUntilPowerUp = MAX_timeUntilPowerUp;

    // Resetting player. Should already be deleted, but just in case, Kill Them
    //if (player) delete player;
    player = CreatePlayer(scene);

    // Swap Scene
    Engine::Get().GetSM().SetActiveScene("Game");
}



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

    ///
    // Scenes
    ///

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
        "SURVIVE to gain POINTs."
        "                                              "
        "THINGs will gradually get MORE INTENSE."
        "                                              "
        "Press [Z] to START!",
        Color{ 1, 1, 1, 1 }, 720);
    Text* textCredits = new Text(engine.GetFont()); textCredits->Create(engine.GetRenderer(), "[heavily inspired by UNDERTALE/deltarune]", Color{ 1, 1, 1, 1 });
    
    // Game scene
    Scene* gameScene = new Scene("Game");
    Text* textPoints = new Text(engine.GetFont()); textTitle->Create(engine.GetRenderer(), "0 POINTs", Color{ 1, 1, 1, 1 });
    // Player
    Player* player = nullptr;

    // Death scene
    Scene* deathScene = new Scene("Death");
   
    // Adding scenes to SceneManager
    engine.GetSM().AddScene(menuScene);
    engine.GetSM().AddScene(gameScene);
    engine.GetSM().AddScene(deathScene);
    engine.GetSM().SetActiveScene("Menu");

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



        ///
        // Scenes
        ///

        if (engine.GetSM().GetActiveScene() == menuScene) 
        {
            textTitle->Draw(engine.GetRenderer(), 32, 32);
            textInstructions->Draw(engine.GetRenderer(), 32, 160);
            textCredits->Draw(engine.GetRenderer(), 32, RESOLUTION_Y - 82);
            if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_Z)) {
                StartGame(gameScene, player);
            }
        }
        else if (engine.GetSM().GetActiveScene() == gameScene) {
            // POINTs
            points += delta;
            textPoints->Create(engine.GetRenderer(), std::to_string((int)points) + " POINTs", Color{ 1, 1, 1, 1 });
            textPoints->Draw(engine.GetRenderer(), RESOLUTION_Xf * 0.45f, 16);

            // Spawn Timers
            if (MAX_timeUntilBullet > 0.75f) MAX_timeUntilBullet -= delta * 0.075f;
            if (MAX_timeUntilEnemy > 0.75f) MAX_timeUntilEnemy -= delta * 0.075f;
            if (MAX_timeUntilPowerUp > 3.75f) MAX_timeUntilPowerUp -= delta * 0.1f;

            // Spawning Enemies
            if (timeUntilEnemy <= 0.f) {
                timeUntilEnemy = MAX_timeUntilEnemy;
                CreateEnemy(gameScene, player);

            } 
            else timeUntilEnemy -= delta;

            // Spawning Power-Ups
            if (timeUntilPowerUp <= 0.f) {
                timeUntilPowerUp = MAX_timeUntilPowerUp;
                CreatePowerUp(gameScene, player);

            }
            else timeUntilPowerUp -= delta;

            // TODO: Spawning Bullets
            if (timeUntilBullet <= 0.f) {
                timeUntilBullet = MAX_timeUntilBullet;
                CreateBullet(gameScene);

            }
            else timeUntilBullet -= delta;

            // Death
            if (player == nullptr || player->IsDestroyed()) {
                engine.GetSM().SetActiveScene("Death");
            }
        }
        else if (engine.GetSM().GetActiveScene() == deathScene) {
            textTitle->Create(engine.GetRenderer(), "YOU HAVE REACHED AN END. CONTINUE?", Color{ 1, 1, 1, 1 });
            textTitle->Draw(engine.GetRenderer(), 32, 32);
            textInstructions->Create(engine.GetRenderer(), 
                "[Z] Retry"
                "                                              "
                "[X] Exit",
                Color{ 1, 1, 1, 1 }, 400);
            textInstructions->Draw(engine.GetRenderer(), 32, 160);
            textCredits->Create(engine.GetRenderer(), std::to_string((int)points) + " POINTs acquired last run", Color{ 1, 1, 1, 1 });
            textCredits->Draw(engine.GetRenderer(), 32, RESOLUTION_Y - 82);
            // Restarting
            if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_Z)) {
                StartGame(gameScene, player);
            }
        }



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