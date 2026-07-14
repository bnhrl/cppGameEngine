#include "pch.h"
#include "Renderer.h"


#include <iostream>
#include "Vector2.h"

namespace bnhe
{
    int Renderer::m_width = 1280;
    int Renderer::m_height = 720;

	bool Renderer::Initialize(const char* name, int w, int h) {
        Renderer::m_width = w;
        Renderer::m_height = h;
        
        m_window = SDL_CreateWindow(name, m_width, m_height, 0);
        if (m_window == nullptr) {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return false;
        }

        m_renderer = SDL_CreateRenderer(m_window, NULL);
        if (m_renderer == nullptr) {
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return false;
        }

        SDL_SetRenderVSync(m_renderer, 1); 

		return true;
	}



    // RenderPresent, Clearing, etc.
    void Renderer::Present()
    {
        SDL_RenderPresent(m_renderer);
    }

    void Renderer::Clear() {
        SDL_RenderClear(m_renderer);
    }

    void Renderer::ShutDown()
    {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }



    // Color?
    void Renderer::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const 
    {
        SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
    }

    void Renderer::SetColor(Color color) const
    {
        SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    }



    // Shape/Point Drawing
    void Renderer::DrawPoint(float x, float y) const
    {
        SDL_RenderPoint(m_renderer, x, y);
    }

    void Renderer::DrawLine(float x1, float y1, float x2, float y2) const
    {
        SDL_RenderLine(m_renderer, x1, y1, x2, y2);
    }

    void Renderer::DrawRect(SDL_FRect rect) const
    {
        SDL_RenderRect(m_renderer, &rect);
    }
    void Renderer::DrawRect(float x, float y, float w, float h) const
    {
        SDL_FRect rect{ x, y, w, h };
        DrawRect(rect);
    }
    void Renderer::DrawRect(Vector2 center, Vector2 size) const
    {
        SDL_FRect rect{ center.x - size.x / 2.0f, center.y - size.y / 2.0f, size.x, size.y };
        DrawRect(rect);
    }

    void Renderer::DrawFillRect(SDL_FRect rect) const
    {
        SDL_RenderFillRect(m_renderer, &rect);
    }
    void Renderer::DrawFillRect(float x, float y, float w, float h) const
    {
        SDL_FRect rect{ x, y, w, h };
        DrawFillRect(rect);
    }
    void Renderer::DrawFillRect(const Vector2 center, const Vector2 size) const
    {
        SDL_FRect rect{ center.x - size.x / 2.0f, center.y - size.y / 2.0f, size.x, size.y };
        DrawFillRect(rect);
    }
}