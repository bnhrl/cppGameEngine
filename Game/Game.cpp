#include "Engine.h"

#include <iostream>
#include <SDL3/SDL.h>

const int RESOLUTION_X = 1920;
const int RESOLUTION_Y = 1200;

using namespace bnhe;

int main()
{
   Renderer r = Renderer();
   r.Initialize("Game Engine", RESOLUTION_X, RESOLUTION_Y);

    //fnEngine();
    SDL_Init(SDL_INIT_VIDEO);


    SDL_Event e;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        r.SetColor(0, 0, 0, 255); // Set render draw color to black
        r.Clear(); // Clear the renderer

        /* Test Rectangle
        r.SetColor(0,255,0,255); // Set render draw color to green
        r.DrawFillRect(270, 190, 200, 200); // Render rectangle
        */

        // Static!
        for (int i = 0; i < 10000; i++) {
            r.SetColor(rand() % 256, rand() % 256, rand() % 256, 255);
            r.DrawPoint(rand() % RESOLUTION_X, rand() % RESOLUTION_Y);
        }

        // Rectangles!
        for (int i = 0; i < 15; i++) {
            int rectangle_size = 100;
            r.SetColor(rand() % 256, rand() % 256, rand() % 256, 255);
            if (rand() % 2 == 0)
                r.DrawFillRect(rand() % RESOLUTION_X, rand() % RESOLUTION_Y, rand() % (rectangle_size + 1), rand() % (rectangle_size+1));
            else
                r.DrawRect(rand() % RESOLUTION_X, rand() % RESOLUTION_Y, rand() % (rectangle_size + 1), rand() % (rectangle_size + 1));
        }

        // Lines!
        for (int i = 0; i < 25; i++) {
            r.SetColor(rand() % 256, rand() % 256, rand() % 256, 255);
            r.DrawLine(rand() % RESOLUTION_X, rand() % RESOLUTION_Y, rand() % RESOLUTION_X, rand() % RESOLUTION_Y);
        }

        r.Present(); // Render the screen
    }

    r.ShutDown();

    return 0;
}
