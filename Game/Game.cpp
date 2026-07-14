#include "Engine.h"

#include <iostream>
#include <SDL3/SDL.h>

#include <vector>

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
    Random::SetResolution(1920, 1200);
    Renderer renderer = Renderer();
    renderer.Initialize("Game Engine", RESOLUTION_X, RESOLUTION_Y);

    Input input;
    input.Initialize();

    Time time = Time();

    ///
    // Values
    ///

    // Drawing
    std::vector<Vector2> points;
    Vector2* prevPoint = nullptr;
    Color backgroundColor = Color(0, 0, 0);
    Color color = Color();
    int minDrawDistance = 15;

    // Player
    Mesh mesh0{ {Vector2(-4,0),Vector2(-2,-4),Vector2(0,-2),Vector2(1,-5),Vector2(2,5),Vector2(3,1),Vector2(7,0)}, Color(0.f, 1.f, 0.f)};
    Mesh mesh1{ {Vector2(-4,0),Vector2(-2,4),Vector2(0,2),Vector2(1,5),Vector2(2,-5),Vector2(3,-1),Vector2(7,0)}, Color(1.f, 0.f, 1.f) };
    Model model = { {mesh0, mesh1} };
    Actor player{ Transform(Vector2(RESOLUTION_X / 2.0f, RESOLUTION_Y / 2.0f), 0.0f, Vector2(16.0f)), model };
    float speed = 2000.0f;

    // Test menu
    Vector2 menuPosOpen = Vector2(RESOLUTION_Xf / 2.0f, RESOLUTION_Yf / 2.0f);
    Vector2 menuPosClosed = Vector2(-RESOLUTION_Xf / 2.0f, RESOLUTION_Yf / 2.0f);
    Vector2 menuPos = menuPosClosed;
    bool menuOpen = false;


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

        if (input.GetMouseDown(Input::MouseButton::Right)) {
            if (points.size() >= 1) {
                points.pop_back();
            }
        }

        // Player movement
        Vector2 force = Vector2(0, 0);
        if (input.GetKeyDown(SDL_SCANCODE_W)) force.y = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_A)) force.x = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_S)) force.y = +speed;
        if (input.GetKeyDown(SDL_SCANCODE_D)) force.x = +speed;

        player.SetVelocity(player.GetVelocity() + force * time.GetDeltaTime());
        player.Update(time.GetDeltaTime());
        player.SetRotation(player.GetTransform().position.AngleBetween(input.GetMousePosition()));

        // Test menu
        if (input.GetKeyPressed(SDL_SCANCODE_TAB)) menuOpen = !menuOpen;



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

        // Player
        player.Draw(renderer);

        // Menu
        renderer.SetColor(0, 0, 1.f);
        if (menuOpen) { menuPos = menuPos.Lerp(menuPosOpen, 16.0f, time.GetDeltaTime()); }
        else { menuPos = menuPos.Lerp(menuPosClosed, 16.0f, time.GetDeltaTime());; }
        renderer.DrawRect(menuPos, Vector2(1280, 640));

        renderer.Present(); // Render the screen
    }



    ///
    // SHUTDOWN
    ///
    renderer.ShutDown();

    return 0;
}
