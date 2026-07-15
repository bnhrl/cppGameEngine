#pragma once

#include <SDL3/SDL.h>
#include "Color.h"
#include "Vector2.h"
#include "Model.h"
#include "Mesh.h"
#include "Transform.h"

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
		void DrawLine(float x1, float y1, float x2, float y2) const;
		void DrawRect(float x, float y, float w, float h) const;
		void DrawRect(SDL_FRect rect) const;
		void DrawRect(Vector2 center, Vector2 size) const;
		void DrawFillRect(float x, float y, float w, float h) const;
		void DrawFillRect(SDL_FRect rect) const;
		void DrawFillRect(Vector2 center, Vector2 size) const;
		void DrawModel(const Model& model, const Transform& transform) const;

		static int GetWidth()  { return m_width; }
		static int GetHeight() { return m_height; }
	private:
		SDL_Renderer* m_renderer = nullptr;
		SDL_Window*   m_window   = nullptr;

		static int m_width;
		static int m_height;
	};
}