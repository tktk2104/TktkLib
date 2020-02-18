#include "TktkDirectX11Wrapper/Sound/SoundManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	CfpPtr<SoundUpdater> SoundManager::m_updater;

	void SoundManager::setUp()
	{
		m_updater = ComponentFrameworkProcessor::addClass(true, new SoundUpdater());
	}

	void SoundManager::load(int id, const std::string & fileName)
	{
		m_updater->load(id, fileName);
	}

	void SoundManager::play(int id, bool loopPlay)
	{
		m_updater->play(id, loopPlay);
	}

	void SoundManager::stop(int id)
	{
		m_updater->stop(id);
	}

	void SoundManager::pause(int id)
	{
		m_updater->pause(id);
	}

	void SoundManager::setMasterVolume(float volume)
	{
		m_updater->setMasterVolume(volume);
	}
}