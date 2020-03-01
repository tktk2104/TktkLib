#include "TktkDirectX11Wrapper/Sound/SoundManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	CfpPtr<SoundUpdater> SoundManager::m_updater;

	void SoundManager::setUp()
	{
		m_updater = ComponentFrameworkProcessor::addClass(true, new SoundUpdater());
	}

	void SoundManager::setMasterVolume(float volume)
	{
		m_updater->setMasterVolume(volume);
	}

	void SoundManager::loadImpl(int id, const std::string & fileName)
	{
		m_updater->load(id, fileName);
	}

	void SoundManager::playImpl(int id, bool loopPlay)
	{
		m_updater->play(id, loopPlay);
	}

	void SoundManager::stopImpl(int id)
	{
		m_updater->stop(id);
	}

	void SoundManager::pauseImpl(int id)
	{
		m_updater->pause(id);
	}
}