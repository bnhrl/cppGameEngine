#include "pch.h"
#include "Renderer/Renderer.h"

#include "Math/Vector2.h"
#include "Renderer/Model.h"

#include <cmath>

namespace bnhe
{
    int Renderer::m_width = 1280;
    int Renderer::m_height = 720;

	bool Renderer::Initialize(const char* name, int w, int h) {
        std::cout << "Renderer initialized!" << "\n";
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

        if (!TTF_Init()) {
            std::cerr << "TTF_Init Error: " << SDL_GetError() << std::endl;
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

    void Renderer::Shutdown()
    {
        TTF_Quit();
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }



    // Color?
    void Renderer::SetColor(float r, float g, float b, float a) const
    {
        r = math::Clamp(r * 255.f, 0.f, 255.f);
        g = math::Clamp(g * 255.f, 0.f, 255.f);
        b = math::Clamp(b * 255.f, 0.f, 255.f);
        a = math::Clamp(a * 255.f, 0.f, 255.f);
        SDL_SetRenderDrawColor(m_renderer, (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a);
    }

    void Renderer::SetColor(Color color) const
    {
        SetColor(color.r, color.g, color.b, color.a);
    }



    // Shape/Point Drawing
    void Renderer::DrawPoint(float x, float y) const
    {
        SDL_RenderPoint(m_renderer, x, y);
    }

    void Renderer::DrawPoint(Vector2 position) const 
    {
        SDL_RenderPoint(m_renderer, position.x, position.y);
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

    void Renderer::DrawModel(const Model& model, const Transform& transform) const {

        for (auto mesh : model.GetMeshes()) {
            SetColor(mesh.GetColor());
            const auto points = mesh.GetPoints();

            for (int i = 0; i < points.size() - 1; i++) {
                // Local space
                Vector2 v1 = points[i];
                Vector2 v2 = points[i + 1];

                // Convert to world space
                v1 *= transform.scale;
                v2 *= transform.scale;

                v1 = v1.Rotate(transform.rotation);
                v2 = v2.Rotate(transform.rotation);

                v1 += transform.position;
                v2 += transform.position;

                DrawLine(v1.x, v1.y, v2.x, v2.y);
            }
        }
    }

    void Renderer::DrawTexture(const Texture& texture, float x, float y, float rotation, Vector2 scale, Color modulate, bool flipH) const
    {
        Vector2 size = texture.GetSize();

        SDL_FRect destRect;
        destRect.w = size.x * scale.x;
        destRect.h = size.y * scale.y;

        destRect.x = x - (destRect.w * 0.5f);
        destRect.y = y - (destRect.h * 0.5f);

        Color color = modulate.ToUint8_T();
        SDL_SetTextureColorMod(texture.m_texture, color.r, color.g, color.b);
        SDL_SetTextureBlendMode(texture.m_texture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(texture.m_texture, color.a);

        // https://wiki.libsdl.org/SDL3/SDL_RenderTexture
        if (flipH)
            SDL_RenderTextureRotated(m_renderer, texture.m_texture, NULL, &destRect, math::RadToDeg(rotation), NULL, SDL_FLIP_HORIZONTAL);
        else 
            SDL_RenderTextureRotated(m_renderer, texture.m_texture, NULL, &destRect, math::RadToDeg(rotation), NULL, SDL_FLIP_NONE);
    }

    void Renderer::DrawTexture(const Texture& texture, const Transform& transform, Color modulate, bool flipH) const
    {
        Vector2 size = texture.GetSize();

        SDL_FRect destRect;
        destRect.w = size.x * transform.scale.x;
        destRect.h = size.y * transform.scale.y;

        destRect.x = transform.position.x - (destRect.w * 0.5f);
        destRect.y = transform.position.y - (destRect.h * 0.5f);

        Color color = modulate.ToUint8_T();
        SDL_SetTextureColorMod(texture.m_texture, color.r, color.g, color.b);
        SDL_SetTextureBlendMode(texture.m_texture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(texture.m_texture, color.a);

        // https://wiki.libsdl.org/SDL3/SDL_RenderTexture
        if (flipH)
            SDL_RenderTextureRotated(m_renderer, texture.m_texture, NULL, &destRect, math::RadToDeg(transform.rotation), NULL, SDL_FLIP_HORIZONTAL);
        else
            SDL_RenderTextureRotated(m_renderer, texture.m_texture, NULL, &destRect, math::RadToDeg(transform.rotation), NULL, SDL_FLIP_NONE);
    }

    void Renderer::DrawTexture(const Texture& texture, const Transform& transform, const Rect rect, Color modulate, bool flipH) const
    {

    }

}