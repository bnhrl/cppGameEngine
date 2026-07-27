#include "pch.h"
#include "Audio.h"
#include "File.h"
#include <iostream>

namespace bnhe {
	void Audio::Initialize() {
		// Setup
		FMOD::System_Create(&m_audio);

		void* extradriverdata = nullptr;
		m_audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

		// Getting all the sound effects
		auto filenames = GetFilesInDirectory(GetWorkingDirectory());
		FMOD::Sound* sound = nullptr;
		for (const auto& filename : filenames)
		{
			std::string str = GetFileExtension(filename);
			if (str == ".wav") {
				std::string name = GetFilenameNoExtension(filename);
				m_audio->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);
				m_sounds[name] = sound;
				//std::cout << "Added " << name << " " << sound << " to Sounds. \n";
			}
		}

		std::cout << "Audio initialized with sounds: ";
		for (const auto& pair : m_sounds) {
			std::cout << pair.first << " || ";
		}
		std::cout << "\n";
	}

	void Audio::Update() {
		m_audio->update();
	}
}