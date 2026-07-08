#include "Engine.h"

#include <iostream>
#include <SDL3/SDL.h>

#include <vector>

const int RESOLUTION_X = 1920;
const int RESOLUTION_Y = 1200;

const int POINT_COUNT = 999; 

using namespace bnhe;

int main()
{
    ///
    // INITIALIZATION
    ///
    Random::SetResolution(1920, 1200);
    Renderer renderer = Renderer();
    renderer.Initialize("Game Engine", RESOLUTION_X, RESOLUTION_Y);

    Input input;
    input.Initialize();

    Time time = Time();


    // values
    Vector2 position;
    std::vector<Vector2> points;
    float speed = 150.0f;



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
        input.Update();
        time.Tick();



        /// 
        // Input
        ///
        if (input.GetMouseDown(Input::MouseButton::Left)) {
            points.push_back(input.GetMousePosition());
        }

        Vector2 velocity{ 0.0f, 0.0f };
        if (input.GetKeyDown(SDL_SCANCODE_W)) velocity.y = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_A)) velocity.x = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_S)) velocity.y =  speed;
        if (input.GetKeyDown(SDL_SCANCODE_D)) velocity.x =  speed;

        position += velocity * time.GetDeltaTime();



        ///
        // RENDER
        ///
        renderer.SetColor(0, 0, 0, 255); // Set render draw color to black
        renderer.Clear();                // Clear the renderer

        // Lines!
        for (int i = 0; i < 25; i++) {
            renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, 255);
            renderer.DrawLine(input.GetMousePosition().x, input.GetMousePosition().y, position.x, position.y);
        }

        renderer.Present(); // Render the screen
    }



    ///
    // SHUTDOWN
    ///
    renderer.ShutDown();

    return 0;
}
