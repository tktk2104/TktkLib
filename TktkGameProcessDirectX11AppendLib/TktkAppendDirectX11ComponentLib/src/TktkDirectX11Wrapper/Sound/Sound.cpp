#include "TktkDirectX11Wrapper/Sound/Sound.h"

#include <stdexcept>
#include "TktkDirectX11Wrapper/Sound/SoundManager.h"

namespace tktk
{
	void Sound::loadImpl(int id, const std::string & fileName)
	{
		if (id <= 0)
		{
			throw std::runtime_error("SoundId Fraud Value");
		}
		SoundManager::load(id, fileName);
	}

	void Sound::setMasterVolume(float volume)
	{
		SoundManager::setMasterVolume(volume);
	}

	void Sound::playImpl(int id, bool loopPlay)
	{
		SoundManager::play(id, loopPlay);
	}

	void Sound::stopImpl(int id)
	{
		SoundManager::stop(id);
	}

	void Sound::pauseImpl(int id)
	{
		SoundManager::pause(id);
	}

	
}