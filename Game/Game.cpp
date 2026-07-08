#include "Engine.h"

#include <iostream>
#include <SDL3/SDL.h>

#include <vector>

const int RESOLUTION_X = 1920;
const int RESOLUTION_Y = 1200;

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
    Vector2* prevPoint = nullptr;
    Color backgroundColor = Color(0, 0, 0);
    Color color = Color();
    int minDrawDistance = 15;



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
            int index = points.size() - 1;
            if (prevPoint != nullptr) {
                if (prevPoint->DistanceTo(input.GetMousePosition()) > minDrawDistance) {
                    points.push_back(input.GetMousePosition());
                    if (points.size() > 2) prevPoint = &points[index - 1];
                }
            }
            else {
                points.push_back(input.GetMousePosition());
                prevPoint = &points[points.size()-1];
            }
        }



        ///
        // RENDER
        ///
        renderer.SetColor(backgroundColor); // Set render draw color to black
        renderer.Clear();                // Clear the renderer

        // Preview next line
        if (points.size() >= 1) {
            renderer.SetColor(Color(125, 125, 125));
            renderer.DrawLine(points[points.size() - 1].x, points[points.size() - 1].y, input.GetMousePosition().x, input.GetMousePosition().y);
        }

        // Drawing!
        for (int i = 0; i < points.size(); i++) {
            renderer.SetColor(color);
            Vector2 prev;
            if (i == 0) prev = points[i];
            else prev = points[i-1];
            renderer.DrawLine(prev.x, prev.y, points[i].x, points[i].y);
        }

        renderer.Present(); // Render the screen
    }



    ///
    // SHUTDOWN
    ///
    renderer.ShutDown();

    return 0;
}
