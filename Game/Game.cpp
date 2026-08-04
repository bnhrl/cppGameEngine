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

void CreateEnemy(Scene* scene, Player* player) {
    Transform transform;
    if (Random::Int(1)) transform = { Vector2(0, Random::PointOnScreen().y), 0.0f, Vector2(4.0f) };
    else                transform = { Vector2(RESOLUTION_X, Random::PointOnScreen().y), 0.0f, Vector2(4.0f) };
    std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(Enemy(transform, Models::PlayerModel()));
    enemy->SetTarget(player);
    scene->AddActor(std::move(enemy));
}

void CreateBullet(Scene* scene) {
    Transform transform;
    Vector2 direction;
    if (Random::Int(1)) { transform = { Vector2(0, Random::PointOnScreen().y), 0.0f, Vector2(4.0f) }; direction = Vector2(1.f, 0.f); }
    else { transform = { Vector2(RESOLUTION_X, Random::PointOnScreen().y), 0.0f, Vector2(4.0f) }; direction = Vector2(-1.f, 0.f); }
    std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(transform, "Everything", direction, 1200.f, Color(0.f, 1.f, 1.f), 3);
    scene->AddActor(std::move(bullet));
}

void CreatePowerUp(Scene* scene, Player* player) {
    std::unique_ptr<PowerUp> powerUp;
    Transform transform;
    if (Random::Int(1)) transform = { Vector2(0, Random::PointOnScreen().y), 0.0f, Vector2(4.0f) };
    else                transform = { Vector2(RESOLUTION_X, Random::PointOnScreen().y), 0.0f, Vector2(4.0f) };
    Player::SoulMode type = (Player::SoulMode)Random::Int(1, 2);
    if (type == Player::YELLOW)
        powerUp = std::make_unique<PowerUp>(transform, Models::CloverModel(), "Yellow");
    else
        powerUp = std::make_unique<PowerUp>(transform, Models::ThumbsModel(), "Orange");
    powerUp->SetVelocity(transform.position.DirectionTo(player->GetTransform().position) * -200.f);
    scene->AddActor(std::move(powerUp));
}

Player* CreatePlayer(Scene* scene) {
    Transform pTransform = Transform(Vector2(RESOLUTION_X / 2.0f, RESOLUTION_Y / 2.0f), 0.0f, Vector2(4.0f));
    std::unique_ptr<Player> player = std::make_unique<Player>((pTransform));
    Player* ptr = player.get();
    scene->AddActor(std::move(player));
    return ptr;
}

float points = 0.f;
const float MAX_TIME_UNTIL_ENEMY = 5.f;
const float MAX_TIME_UNTIL_BULLET = 5.f;
const float MAX_TIME_UNTIL_POWER_UP = 8.f;
float MAX_timeUntilEnemy = MAX_TIME_UNTIL_ENEMY;
float MAX_timeUntilBullet = MAX_TIME_UNTIL_BULLET;
float MAX_timeUntilPowerUp = MAX_TIME_UNTIL_POWER_UP;
float timeUntilEnemy = MAX_timeUntilEnemy;
float timeUntilBullet = MAX_timeUntilBullet;
float timeUntilPowerUp = MAX_timeUntilPowerUp;


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



// Testing stuff from class
class Object {
public:
    Object() { std::cout << "constructor\n"; }
    ~Object() { std::cout << "destructor\n"; }

    Object(const Object& object) { std::cout << "copy\n"; }
    Object& operator = (const Object& object) { std::cout << "assignemnt\n"; return *this; }

};



int main()
{
    std::cout << "=============== object ===============\n";
    {
        Object objectA;
        Object objectB(objectA);
        Object objectC;
        objectC = objectA;
    }
    std::cout << "=============== raw pointers ===============\n";
    {
        Object* objectA = new Object();
        std::cout << objectA << "\n";
        Object* objectB = new Object(*objectA);
        std::cout << objectB << "\n";
        Object* objectC = nullptr;

        delete objectA;
        delete objectB;
    }
    std::cout << "=============== unique pointers ===============\n";
    {
        std::unique_ptr<Object> objectA = std::make_unique<Object>();
        std::cout << objectA.get() << "\n";
        std::unique_ptr<Object> objectB;
        objectB = std::move(objectA);
        std::cout << objectB.get() << "\n";
        
        objectB.reset();
    }
    std::shared_ptr<Object> objectC;
    std::cout << "=============== shared pointers ===============\n";
    {
        auto objectA = std::make_shared<Object>(); // auto here is the same as std::shared_ptr<Object>
        std::cout << objectA.get() << "\n";
        std::cout << objectA.use_count() << "\n";
        auto objectB = objectA;
        std::cout << objectB.get() << "\n";
        std::cout << objectB.use_count() << "\n";
        objectC = objectA;
    }
    std::cout << objectC.get() << "\n";
    std::cout << objectC.use_count() << "\n";

    std::cout << "\n\n";


    ///
    // INITIALIZATION
    ///

    Engine& engine = Engine::Get();
    engine.Initialize(RESOLUTION_X, RESOLUTION_Y);



    ///
    // Values
    ///

    Color backgroundColor = Color(0, 0, 0);

    // create texture, using shared_ptr so texture can be shared
    std::shared_ptr<Texture> texture = std::make_shared<Texture>();
    texture->Load("flea.png", engine.GetRenderer());




    ///
    // Scenes
    ///
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

        engine.GetRenderer().DrawTexture(texture.get(), 30, 30);

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