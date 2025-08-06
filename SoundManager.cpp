#include "SoundManager.h"
#include <iostream>

SoundManager* SoundManager::Instance = NULL;

SoundManager* SoundManager::get()
{
	if (Instance == NULL)
		Instance = new SoundManager();
	return Instance;
}

SoundManager::SoundManager()
{
	// Setup sound sources
	sf::Sound* curSound;
	for (int i = 0; i < 8; i++)
	{
		curSound = new sf::Sound();
		sounds.push_back(curSound);
	}

	// Setup sound buffers
	auto addSound = [this](std::string filename)
		{
			sf::SoundBuffer* curSoundBuffer = new sf::SoundBuffer();
			curSoundBuffer->loadFromFile("assets/sounds/" + filename + ".wav");
			soundBuffers.push_back(curSoundBuffer);
		};

	addSound("glooby");
	addSound("SwitchOn");
	addSound("SwitchOff");
	addSound("SwitchFail");
	addSound("ButtonRollover");
	addSound("Processing");
	addSound("-");
	addSound("meta");
	addSound("zap");
}

SoundManager::~SoundManager()
{
	for (auto sound : sounds) delete sound;
	for (auto buffer : soundBuffers) delete buffer;

	sounds.clear();
	soundBuffers.clear();
}

void SoundManager::play(sfx sound)
{
	if (!SettingsManager::soundEnabled) return;

	for (int i = 0; i < sounds.size(); i++)
	{
		if (sounds.at(i)->getStatus() != sf::Sound::Playing)
		{
			sounds.at(i)->setBuffer(*soundBuffers.at(sound));
			sounds.at(i)->play();
			return;
		}
	}
}

void SoundManager::playInChannel(sfx sound, int channel)
{
	if (!SettingsManager::soundEnabled) return;

	if (channel < 0 || channel >= sounds.size())
	{
		std::cout << "ERROR: INVALID CHANNEL CALL" << std::endl;
		return;
	}
	sounds.at(channel)->stop();
	sounds.at(channel)->setBuffer(*soundBuffers.at(sound));
	sounds.at(channel)->play();
}

void SoundManager::stopAllSounds()
{
	for (auto& sound : sounds)
	{
		sound->stop();
	}
}

void SoundManager::stopInChannel(int channel)
{
	if (channel < 0 || channel >= sounds.size())
	{
		std::cout << "ERROR: INVALID CHANNEL CALL" << std::endl;
		return;
	}
	sounds.at(channel)->stop();
}