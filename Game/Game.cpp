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



class Animal {
public:
    virtual void speak() { std::cout << "aaa"; }
};

class Cat : public Animal {
    void speak() override { std::cout << "meow"; }
};

class Dog : public Animal {
    void speak() override { std::cout << "BARK!!"; }
};

class Bird : public Animal {
    void speak() override { std::cout << "squawk"; }
};

enum class Type {
    Cat  = 1, 
    Dog  = 2, 
    Bird = 3
};

Animal* AnimalFactory(Type id) {
    Animal* animal = nullptr;
    switch (id) {
    case Type::Cat:
        animal = new Cat;
        break;
    case Type::Dog:
        animal = new Dog;
        break;
    case Type::Bird:
        animal = new Bird;
        break;
    }
    return animal;
}

Animal* AnimalFactory(const std::string& id) {
    Animal* animal = nullptr;
    if      (id == "Cat")  animal = new Cat;
    else if (id == "Dog")  animal = new Dog;
    else if (id == "Bird") animal = new Bird;
    return animal;
}


std::map<std::string, std::unique_ptr<ICreator>> registry;



int main()
{
    //Factory::Instance().Register<Actor>("Actor");
    //auto actor =


    /*registry["Cat"] = std::make_unique<Creator<Cat>>();
    registry["Dog"] = std::make_unique<Creator<Dog>>();

    auto animal = registry["Dog"]->Create();

    return 0;


    std::string selection = "";
    std::cout << "Select animal: ";
    std::cin >> selection;

    auto animal = AnimalFactory(selection);
    if (animal) animal->speak();

    return 0;*/



    ///
    // INITIALIZATION
    ///

    Engine& engine = Engine::Get();
    engine.Initialize(RESOLUTION_X, RESOLUTION_Y);


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
        rapidjson::Document document;
        if (json::Load("data/data.json", document))
        {
            // read the age data (int) from the json
            int age;
            json::Read(document, "age", age);
            // show the age data
            std::cout << age << std::endl;
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