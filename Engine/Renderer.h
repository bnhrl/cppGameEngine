#pragma once

#include <SDL3/SDL.h>

namespace bnhe
{
	class Renderer
	{
	public:
		bool Initialize(const char* name, int w = 1280, int h = 720);

		void Present();
		void Clear();
		void ShutDown();

		void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);

		void DrawPoint(float x, float y);
		void DrawLine(float x1, float y1, float x2, float y2);
		void DrawRect(float x, float y, float w, float h);
		void DrawRect(SDL_FRect rect);
		void DrawFillRect(float x, float y, float w, float h);
		void DrawFillRect(SDL_FRect rect);
	private:
		SDL_Renderer* m_renderer = nullptr;
		SDL_Window*   m_window   = nullptr;
	};
}