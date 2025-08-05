#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SFML/Audio.hpp>
#include <vector>

// Hacked together in 5 seconds by @matthewjberger (???)

class SoundManager
{
private:
	SoundManager();
	
	static SoundManager* Instance;

	std::vector<sf::SoundBuffer*> soundBuffers;
	std::vector<sf::Sound*> sounds;

public:
	~SoundManager();
	static SoundManager* get();
	enum sfx
	{
		GLOOBY,
		SWITCH_ON,
		SWITCH_OFF,
		SWITCH_FAIL,
		ROLLOVER,
		PROCESSING,
		DEATH,
		META
	};

	void play(sfx soundEffect);
	void playInChannel(sfx soundEffect, int channel);
	void stopAllSounds();
	void stopInChannel(int channel);
};

#endif