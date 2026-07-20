#include <iostream>
#include <vector>

#include <SDL3/SDL.h>
#include <fmod.hpp>

#include "Engine.h"
#include "Player.h"

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

    // Player
    Mesh mesh0{ {Vector2(-4,0),Vector2(-2,-4),Vector2(0,-2),Vector2(1,-5),Vector2(2,5),Vector2(3,1),Vector2(7,0)}, Color(0.f, 1.f, 0.f) };
    Mesh mesh1{ {Vector2(-4,0),Vector2(-2,4),Vector2(0,2),Vector2(1,5),Vector2(2,-5),Vector2(3,-1),Vector2(7,0)}, Color(1.f, 0.f, 1.f) };
    Model model = { {mesh0, mesh1} };
    Player player{ 3000.0f, Transform(Vector2(RESOLUTION_X / 2.0f, RESOLUTION_Y / 2.0f), 0.0f, Vector2(16.0f)), model };

    // Drawing
    std::vector<Vector2> points;
    Vector2* prevPoint = nullptr;
    Color backgroundColor = Color(0, 0, 0);
    Color color = Color();
    int minDrawDistance = 15;

    // Test menu
    Vector2 menuPosOpen = Vector2(RESOLUTION_Xf / 2.0f, RESOLUTION_Yf / 2.0f);
    Vector2 menuPosClosed = Vector2(-RESOLUTION_Xf / 2.0f, RESOLUTION_Yf / 2.0f);
    Vector2 menuPos = menuPosClosed;
    bool menuOpen = false;

    // Scene
    Scene scene = Scene();
    scene.AddActor(&player);

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

        // Drawing
        if (engine.GetInput().GetMouseDown(Input::MouseButton::Left)) {
            int index = points.size() - 1;
            if (prevPoint != nullptr) {
                if (prevPoint->DistanceTo(engine.GetInput().GetMousePosition()) > minDrawDistance) {
                    points.push_back(engine.GetInput().GetMousePosition());
                    if (points.size() > 2) prevPoint = &points[index - 1];
                }
            }
            else {
                points.push_back(engine.GetInput().GetMousePosition());
                prevPoint = &points[points.size()-1];
            }
        }

        if (engine.GetInput().GetMouseDown(Input::MouseButton::Right)) {
            if (points.size() >= 1) {
                points.pop_back();
            }
        }

        // Test menu
        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_TAB)) menuOpen = !menuOpen;



        ///
        // Render
        ///

        engine.GetRenderer().SetColor(backgroundColor); // Set render draw color to black
        engine.GetRenderer().Clear();                // Clear the renderer

        // Preview next line
        if (points.size() >= 1) {
            engine.GetRenderer().SetColor(Color(125, 125, 125));
            engine.GetRenderer().DrawLine(points[points.size() - 1].x, points[points.size() - 1].y, engine.GetInput().GetMousePosition().x, engine.GetInput().GetMousePosition().y);
        }

        // Drawing!
        for (int i = 0; i < points.size(); i++) {
            engine.GetRenderer().SetColor(color);
            Vector2 prev;
            if (i == 0) prev = points[i];
            else prev = points[i-1];
            engine.GetRenderer().DrawLine(prev.x, prev.y, points[i].x, points[i].y);
        }

        // Menu
        engine.GetRenderer().SetColor(0, 0, 1.f);
        if (menuOpen) { menuPos = menuPos.Lerp(menuPosOpen, 16.0f, delta); }
        else { menuPos = menuPos.Lerp(menuPosClosed, 16.0f, delta);; }
        engine.GetRenderer().DrawRect(menuPos, Vector2(1280, 640));

        scene.Draw(engine.GetRenderer());
        engine.GetRenderer().Present(); // Render the screen



        ///
        // Audio
        ///

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

        audio->update();
    }



    ///
    // SHUTDOWN
    ///

    engine.Shutdown();

    return 0;
}
