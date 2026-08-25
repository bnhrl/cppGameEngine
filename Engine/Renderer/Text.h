#pragma once
#include "Renderer/Renderer.h"
#include "Renderer/Font.h"

struct SDL_Texture;

namespace bnhe {
	class Text {
	public:
		Text() = default;
		Text(res_t<Font> font) : m_font{ font } {}
		~Text();

		bool Create(Renderer& renderer, const std::string& text, const Color& color, int wrap_length = 0);
		const void Draw(const Renderer& renderer, float x, float y) const;

	private:
		res_t<Font> m_font{ nullptr };
		SDL_Texture* m_texture{ nullptr };
	};
}