#include "TktkDX12Game/Sound/Sound.h"

#include <algorithm>

namespace tktk
{
	Sound::Sound(unsigned int soundDataNum)
		: m_assets(soundDataNum)
	{
	}

	void Sound::load(unsigned int id, const std::string & fileName, IXAudio2* xAudioPtr, HANDLE hEvent)
	{
		m_assets.emplaceAt(id, fileName, xAudioPtr, hEvent);
	}

	void Sound::clear()
	{
		m_assets.clear();
	}

	void Sound::play(unsigned int id, bool loopPlay)
	{
		if (!m_assets.at(id)->isPlaySound())
		{
			m_assets.at(id)->playSound(loopPlay);
		}
	}

	void Sound::stop(unsigned int id)
	{
		if (m_assets.at(id)->isPlaySound())
		{
			m_assets.at(id)->stopSound();
		}
	}

	void Sound::pause(unsigned int id)
	{
		if (m_assets.at(id)->isPlaySound())
		{
			m_assets.at(id)->pauseSound();
		}
	}

	void Sound::updatePlayingSound()
	{
		for (unsigned int i = 0; i < m_assets.arrayMaxSize(); i++)
		{
			auto ptr = m_assets.at(i);

			if (ptr != nullptr && ptr->isPlaySound()) ptr->update();
		}
	}
}