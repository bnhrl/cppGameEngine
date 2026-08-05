#pragma once
#include "Renderer.h"
#include "Font.h"

struct SDL_Texture;

namespace bnhe {
	class Text {
	public:
		Text() = default;
		Text(res_t<Font> font) : m_font{ font } {}
		~Text();

		bool Create(Renderer& renderer, const std::string& text, const Color& color, int wrap_length = 0);
		void Draw(Renderer& renderer, float x, float y);

	private:
		res_t<Font> m_font{ nullptr };
		SDL_Texture* m_texture{ nullptr };
	};
}