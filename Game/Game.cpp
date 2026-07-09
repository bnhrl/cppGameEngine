#include "Engine.h"

#include <iostream>
#include <SDL3/SDL.h>

#include <vector>

const int RESOLUTION_X = 1920;
const int RESOLUTION_Y = 1200;
const float RESOLUTION_Xf = RESOLUTION_X;
const float RESOLUTION_Yf = RESOLUTION_Y;

using namespace bnhe;

struct Transform {
    Vector2 position;
    float rotation;
    Vector2 scale;
};

class Actor {
public:
    Actor(Transform transform, Vector2 size = Vector2(64, 64)) : m_transform{ transform }, m_size{ size } {}

    void Update(float delta) {
        m_transform.position += (m_velocity * delta);
        m_velocity = m_velocity.Lerp(Vector2(0, 0), 6.7f, delta);
    
        m_transform.position.x = math::Wrap(m_transform.position.x, 0.0f, RESOLUTION_Xf);
        m_transform.position.y = math::Wrap(m_transform.position.y, 0.0f, RESOLUTION_Yf);
    }
    
    void Draw(const Renderer& renderer) {
        renderer.SetColor(0, 255, 0);
        renderer.DrawRect(m_transform.position, m_size * m_transform.scale);
    }

    const Transform& GetTransform() { return m_transform; }
    const Vector2 GetSize() { return m_size; }
    const Vector2 GetVelocity() { return m_velocity; }

    void SetPosition(const Vector2 position) { m_transform.position = position; }
    void SetRotation(float rotation)         { m_transform.rotation = rotation; }
    void SetScale(const Vector2 scale)       { m_transform.scale = scale; }

    void SetSize(const Vector2 size)         { m_size = size; }
    void SetVelocity(const Vector2 velocity) { m_velocity = velocity; }

protected:
    Transform m_transform;
    Vector2 m_velocity{ 0, 0 };
    Vector2 m_size;
};

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
    Actor player{ Transform(Vector2(RESOLUTION_X / 2.0f, RESOLUTION_Y / 2.0f), 0.0f, Vector2(1.0f)) };
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

        if (input.GetMousePressed(Input::MouseButton::Right)) {
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
        renderer.SetColor(Color(0, 255, 0));
        player.Draw(renderer);
        std::cout << menuPos.x << " " << menuPos.y << "\n";

        // Menu
        renderer.SetColor(0, 0, 255);
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
