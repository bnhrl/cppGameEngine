#pragma once

#include <fmod.hpp>
#include <string>
#include <map>

namespace bnhe {
	class Audio {
	public:
		void Initialize();

		void Update();
		
		FMOD::Sound* GetSound(std::string sound) const { return m_sounds.find(sound)->second; }
		void PlaySound(std::string sound) { m_audio->playSound(GetSound(sound), nullptr, false, nullptr); }

	private:
		FMOD::System* m_audio = nullptr;
		std::map<std::string, FMOD::Sound*> m_sounds;
	};
}