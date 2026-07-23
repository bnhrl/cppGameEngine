#include <iostream>
#include <vector>

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
    // FILESYSTEM
    ///

    // get current working directory
    std::cout << "Directory Operations:\n";
    std::cout << "Working directory: " << GetWorkingDirectory() << "\n";

    // set working directory (current working directory + "Assets")
    std::cout << "Setting directory to 'Assets'...\n";
    SetWorkingDirectory("Assets");
    std::cout << "New directory: " << GetWorkingDirectory() << "\n\n";

    // get filenames in the working directory
    std::cout << "Files in Directory:\n";
    auto filenames = GetFilesInDirectory(GetWorkingDirectory());
    for (const auto& filename : filenames)
    {
        std::cout << filename << "\n";
    }
    std::cout << "\n";

    // get filename info
    if (!filenames.empty())
    {
        // get filename
        std::string str = GetFilename(filenames[0]);
        std::cout << "Filename: " << str << "\n";

        // get extension
        str = GetFileExtension(filenames[0]);
        std::cout << "Extension: " << str << "\n";

        // get filename no extension
        str = GetFilenameNoExtension(filenames[0]);
        std::cout << "Filename No Extension: " << str << "\n\n";
    }

    // read and display text file
    std::cout << "Text File Reading:\n";
    std::string str;
    if (ReadTextFile("test.txt", str))
    {
        std::cout << str << "\n";
    }

    // write to text file
    std::cout << "Text File Writing:\n";
    WriteTextFile("test.txt", "Hello, World!", true);
    if (ReadTextFile("test.txt", str))
    {
        std::cout << str << "\n";
    }



    ///
    // INITIALIZATION
    ///

    Engine& engine = Engine::Get();
    engine.Initialize(RESOLUTION_X, RESOLUTION_Y);



    ///
    // AUDIO SYSTEM
    ///

    FMOD::System* audio;
    FMOD::System_Create(&audio);

    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);



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
    Mesh enemyMesh0{ {Vector2(4,4),Vector2(-4,-4)}, Color(1,0,0) };
    Mesh enemyMesh1{ {Vector2(4,-4),Vector2(-4,4)}, Color(1,0.5,0) };
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

    // Sounds
    std::vector<FMOD::Sound*> sounds;

    FMOD::Sound* sound = nullptr;
    audio->createSound("test_0.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);
    audio->createSound("test_1.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);
    audio->createSound("test_2.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);


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
            audio->playSound(sounds[0], nullptr, false, nullptr);
        }
        else if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_2))
        {
            audio->playSound(sounds[1], nullptr, false, nullptr);
        }
        else if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_3))
        {
            audio->playSound(sounds[2], nullptr, false, nullptr);
        }



        ///
        // Render
        ///

        engine.GetRenderer().SetColor(backgroundColor); // Set render draw color to black
        engine.GetRenderer().Clear();                // Clear the renderer

        // Test Menu
        engine.GetRenderer().SetColor(0, 0, 1.f);
        if (menuOpen) { menuPos = menuPos.Lerp(menuPosOpen, 16.0f, delta); }
        else { menuPos = menuPos.Lerp(menuPosClosed, 16.0f, delta);; }
        engine.GetRenderer().DrawRect(menuPos, Vector2(1280, 640));

        scene.Draw(engine.GetRenderer());
        engine.GetRenderer().Present(); // Render the screen



        ///
        // Audio
        ///

        audio->update();
    }



    ///
    // SHUTDOWN
    ///

    engine.Shutdown();

    return 0;
}
