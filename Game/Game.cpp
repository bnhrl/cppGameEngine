#include <iostream>
#include <vector>
#include <fstream>
#include <map>

#include <SDL3/SDL.h>
#include <fmod.hpp>

#include "Engine.h"

#include "Player.h"
#include "Models.h"

const int RESOLUTION_X = 1280;
const int RESOLUTION_Y = 960;
const float RESOLUTION_Xf = RESOLUTION_X;
const float RESOLUTION_Yf = RESOLUTION_Y;

using namespace bnhe;



std::map<std::string, std::unique_ptr<ICreator>> registry;



int main()
{
    ///
    // INITIALIZATION
    ///

    Engine& engine = Engine::Get();
    engine.Initialize(RESOLUTION_X, RESOLUTION_Y);

    ///
    // Factory Testing
    ///

   /* Factory::Instance().Register<Actor>("Actor");
    Factory::Instance().Register<Object>("Object");

    auto actor = Factory::Instance().Create<Actor>("Actor");
    std::cout << actor->IsActive() << std::endl;

    auto object = Factory::Instance().Create<Object>("Object");
    std::cout << object->IsActive() << std::endl;

    json::document_t document;
    if (json::Load("data/scene.json", document)) {
        object->Read(document);
        std::cout << object->GetName();
    }*/

    ///
    // JSON Testing
    ///

    // load the json data from a file
    std::string buffer;
    if (ReadTextFile("data/data.json", buffer))
    {
        // show the contents of the json file (debug)
        std::cout << buffer << std::endl;

        // create json document from the json file contents
        json::document_t document;
        if (json::Load("data/data.json", document))
        {
            // read the age data (int) from the json
            int age;
            std::string name;
            float speed;
            bool isAwake;
            Vector2 position;
            Color color;

            // read the data
            JSON_READ(document, age);
            JSON_READ(document, name);
            JSON_READ(document, speed);
            JSON_READ(document, isAwake);
            JSON_READ(document, position);
            JSON_READ(document, color);

            // show the data
            std::cout << "age: " << age << std::endl;
            std::cout << "name: " << name << std::endl;
            std::cout << "speed: " << speed << std::endl;
            std::cout << "isAwake: " << isAwake << std::endl;
            std::cout << "position: " << position.x << " " << position.y << std::endl;
            std::cout << "color: " << color.r << " " << color.g << " " << color.b << " " << color.a << std::endl;
        }
    }



    ///
    // Values
    ///

    Color backgroundColor = Color(0, 0, 0);



    ///
    // Scenes
    ///
    Scene* menuScene = new Scene("Menu");



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




        ///
        // Render
        ///

        if (engine.GetSM().GetActiveScene())
            engine.GetSM().GetActiveScene()->Draw(engine.GetRenderer());
        engine.GetPS().Draw(engine.GetRenderer());
        engine.GetRenderer().Present(); // Render the screen

        engine.GetRenderer().SetColor(backgroundColor); // Set render draw color to black
        engine.GetRenderer().Clear();                   // Clear the renderer
        engine.UpdateAudio();
    }



    ///
    // SHUTDOWN
    ///

    engine.Shutdown();

    return 0;
}