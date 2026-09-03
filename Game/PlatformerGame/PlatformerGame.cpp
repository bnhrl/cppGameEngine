#include "pch.h"
#include "PlatformerGame.h"

#include "PlatformerPlayer.h"
#include "PlatformerEnemy.h"

int PlatformerGame::Run() 
{
    ///
    // INITIALIZATION
    ///

    SetWorkingDirectory("PlatformerGame/Assets");
    Engine& engine = Engine::Get();
    engine.Initialize(RESOLUTION_X, RESOLUTION_Y);


    // Menu Scene
    Scene* menuScene = new Scene("Menu");
    Text* textTitle = new Text(engine.GetFontBig()); textTitle->Create(engine.GetRenderer(), "UNNAMED C++ GAME", Color{ 1, 1, 1, 1 });
    Text* textInstructions = new Text(engine.GetFont());
    textInstructions->Create(engine.GetRenderer(),
        "[ARROW KEYS] to MOVE."
        "                                              "
        "Press [X] to DASH ATTACK."
        "                                              "
        "Press [Z] to START!",
        Color{ 1, 1, 1, 1 }, 720);

    float points = 0.f;

    // Game Scene
    Scene* gameScene = new Scene("Game");
    gameScene->Load("Scenes/scene.json");

    std::unique_ptr<PlatformerPlayer> player = Factory::Instance().Create<PlatformerPlayer>("PlayerPrototype");
    PlatformerPlayer* playerRef = player.get();
    gameScene->AddActor(std::move(player));

    // Game Over Scene
    Scene* gameOverScene = new Scene("Game Over");
    Text* textGameOver = new Text(engine.GetFontBig()); textTitle->Create(engine.GetRenderer(), "GAME OVER", Color{ 1, 1, 1, 1 });


    // Scene setup
    engine.GetSM().AddScene(menuScene);
    engine.GetSM().AddScene(gameScene);




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

        engine.Update();

        if (engine.GetSM().GetActiveScene())
            engine.GetSM().GetActiveScene()->Draw(engine.GetRenderer());
        engine.GetPS().Draw(engine.GetRenderer());
        engine.GetRenderer().Present(); // Render the screen

        engine.GetRenderer().SetColor(Color(0,0,0)); // Set render draw color to black
        engine.GetRenderer().Clear();                // Clear the renderer
        engine.UpdateAudio();

        Scene* activeScene = engine.GetSM().GetActiveScene();
        if (activeScene == menuScene)
        {
            textTitle->Draw(engine.GetRenderer(), 32, 32);
            textInstructions->Draw(engine.GetRenderer(), 32, 160);
            if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_Z)) 
            {
                points = 0.f;
                engine.GetSM().SetActiveScene("Game");
                std::unique_ptr<PlatformerEnemy> enemy = Factory::Instance().Create<PlatformerEnemy>("EnemyPrototype");
                enemy->SetTarget(playerRef);
                gameScene->AddActor(std::move(enemy));
            }
        }
        else if (activeScene == gameScene)
        {
            if (!playerRef or playerRef->IsDestroyed()) engine.GetSM().SetActiveScene("Game Over");
        }
        else if (activeScene == gameOverScene)
        {
            textGameOver->Draw(engine.GetRenderer(), 32, 32);
            if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_Z)) {
                engine.GetSM().SetActiveScene("Menu");
            }
        }

    }
    engine.Shutdown();
    return 0;
}