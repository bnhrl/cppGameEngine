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
    std::vector<Vector2> points;
    Color color = Color();



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

        



        ///
        // RENDER
        ///
        renderer.SetColor(0, 0, 0, 255); // Set render draw color to black
        renderer.Clear();                // Clear the renderer

        // Lines!
        for (int i = 0; i < points.size(); i++) {
            renderer.SetColor(color);
            renderer.DrawLine(input.GetMousePosition().x, input.GetMousePosition().y, points[i].x, points[i].y);
        }

        renderer.Present(); // Render the screen
    }



    ///
    // SHUTDOWN
    ///
    renderer.ShutDown();

    return 0;
}
