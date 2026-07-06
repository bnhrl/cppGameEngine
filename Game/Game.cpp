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

    //SDL_Init(SDL_INIT_VIDEO);
    //fnEngine();
    SDL_Event e;

    ///
    // MAIN LOOP
    ///
    bool quit = false;

    std::vector<Vector2> v;

    for (int i = 0; i < POINT_COUNT; i++) {
        Vector2 vec;

        v.push_back(vec);
        v[i] = Vector2(Random::PointOnScreenX(), Random::PointOnScreenY());
    }

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
        // RENDER
        ///
        renderer.SetColor(0, 0, 0, 255); // Set render draw color to black
        renderer.Clear();                // Clear the renderer

        // Static! (Points)
        for (int i = 0; i < POINT_COUNT; i++) {
            renderer.SetColor(Random::Int(256), Random::Int(256), Random::Int(256), 255);
            renderer.DrawPoint(v[i].x, v[i].y);
        }

        //// Rectangles!
        //for (int i = 0; i < 15; i++) {
        //    int rectangle_size = 100;
        //    renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, 255);
        //    if (rand() % 2 == 0)
        //        renderer.DrawFillRect(Random::PointOnScreenX(), Random::PointOnScreenX(), Random::Int(rectangle_size), Random::Int(rectangle_size));
        //    else
        //        renderer.DrawRect(Random::PointOnScreenX(), Random::PointOnScreenX(), Random::Int(rectangle_size), Random::Int(rectangle_size));
        //}

        //// Lines!
        //for (int i = 0; i < 25; i++) {
        //    renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, 255);
        //    renderer.DrawLine(Random::PointOnScreenX(), Random::PointOnScreenY(), Random::PointOnScreenX(), Random::PointOnScreenY());
        //}

        renderer.Present(); // Render the screen
    }

    ///
    // SHUTDOWN
    ///
    renderer.ShutDown();

    return 0;
}
