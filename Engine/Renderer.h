#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>


#include "Math/Color.h"
#include "Math/Vector2.h"
#include "Model.h"
#include "Mesh.h"
#include "Texture.h"
#include "Math/Transform.h"
#include "Math/Rect.h"

namespace bnhe
{
	class Renderer
	{
	public:
		bool Initialize(const char* name, int w = 1280, int h = 720);

		void Present();
		void Clear();
		void Shutdown();

		//void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255) const;
		void SetColor(float r, float g, float b, float a = 255) const;
		void SetColor(Color color) const;

		void DrawPoint(float x, float y) const;
		void DrawPoint(Vector2 position) const;
		void DrawLine(float x1, float y1, float x2, float y2) const;
		void DrawRect(float x, float y, float w, float h) const;
		void DrawRect(SDL_FRect rect) const;
		void DrawRect(Vector2 center, Vector2 size) const;
		void DrawFillRect(float x, float y, float w, float h) const;
		void DrawFillRect(SDL_FRect rect) const;
		void DrawFillRect(Vector2 center, Vector2 size) const;
		void DrawModel(const Model& model, const Transform& transform) const;
		void DrawTexture(const Texture& texture, float x, float y, float rotationDegrees = 0.f, Vector2 scale = Vector2(1.f), Color modulate = Color(1.f, 1.f, 1.f, 1.f), bool flipH = false) const;
		void DrawTexture(const Texture& texture, const Transform& transform, Color modulate = Color(1.f, 1.f, 1.f, 1.f), bool flipH = false) const;
		void DrawTexture(const Texture& texture, const Transform& transform, const Rect rect, Color modulate = Color(1.f, 1.f, 1.f, 1.f), bool flipH = false) const;

		static int GetWidth()  { return m_width; }
		static int GetHeight() { return m_height; }
	private:
		SDL_Renderer* m_renderer = nullptr;
		SDL_Window*   m_window   = nullptr;

		static int m_width;
		static int m_height;

		friend class Text;
		friend class Texture;
	};
}