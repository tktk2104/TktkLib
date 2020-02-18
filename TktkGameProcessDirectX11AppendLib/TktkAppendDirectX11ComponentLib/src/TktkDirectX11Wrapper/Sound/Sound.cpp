#include "TktkDirectX11Wrapper/Sound/Sound.h"

#include <stdexcept>
#include "TktkDirectX11Wrapper/Sound/SoundManager.h"

namespace tktk
{
	void Sound::load(int id, const std::string & fileName)
	{
		if (id <= 0)
		{
			throw std::runtime_error("SoundId Fraud Value");
		}
		SoundManager::load(id, fileName);
	}

	void Sound::play(int id, bool loopPlay)
	{
		SoundManager::play(id, loopPlay);
	}

	void Sound::stop(int id)
	{
		SoundManager::stop(id);
	}

	void Sound::pause(int id)
	{
		SoundManager::pause(id);
	}

	void Sound::setMasterVolume(float volume)
	{
		SoundManager::setMasterVolume(volume);
	}
}