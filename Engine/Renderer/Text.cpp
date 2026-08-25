#include "pch.h"
#include "Renderer/Text.h"

namespace bnhe {
	Text::~Text() {
		if (m_texture != nullptr) {
			SDL_DestroyTexture(m_texture);
		}
	}

	bool Text::Create(Renderer& renderer, const std::string& text, const Color& color, int wrap_length) {
		// create a surface using the font, text string and color
		SDL_Color c{ (uint8_t)(color.r * 255), (uint8_t)(color.g * 255), (uint8_t)(color.b * 255), 255 };
		SDL_Surface* surface = nullptr;
		if (wrap_length <= 0) surface = TTF_RenderText_Solid(m_font->m_ttfFont, text.c_str(), text.size(), c);
		else surface = TTF_RenderText_Solid_Wrapped(m_font->m_ttfFont, text.c_str(), text.size(), c, wrap_length);
		if (surface == nullptr) {
			std::cerr << "Could not create surface.\n";
			return false;
		}

		// create a texture from the surface, only textures can render to the renderer
		m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
		if (m_texture == nullptr) {
			SDL_DestroySurface(surface);
			std::cerr << "Could not create texture" << SDL_GetError() << std::endl;
			return false;
		}

		// free the surface, no longer needed after creating the texture
		SDL_DestroySurface(surface);

		return true;
	}

	const void Text::Draw(const Renderer& renderer, float x, float y) const {
		// get the texture width and height
		float width, height;
		bool success = SDL_GetTextureSize(m_texture, &width, &height);
		assert(success);

		// set the texture into the renderer at rect 
		SDL_FRect rect{ x, y, width, height };
		success = SDL_RenderTexture(renderer.m_renderer, m_texture, NULL, &rect);
		assert(success);
	}
}