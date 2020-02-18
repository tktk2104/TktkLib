#include "TktkDirectX11Wrapper/Sound/SoundUpdater.h"

#include <stdexcept>
#include <TktkMath/MathHelper.h>
#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	SoundUpdater::SoundUpdater()
	{
		CoInitializeEx(NULL, COINIT_MULTITHREADED);

		m_soundEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		if (m_soundEvent == NULL)
		{
			throw std::runtime_error("SoundEvent create error");
		}

		HRESULT hr;

		hr = XAudio2Create(&m_xAudioPtr, 0, XAUDIO2_DEFAULT_PROCESSOR);
		if (FAILED(hr))
		{
			throw std::runtime_error("XAudio2 create error");
		}

		hr = m_xAudioPtr->CreateMasteringVoice(&m_masterVoicePtr, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, 0, NULL);
		if (FAILED(hr))
		{
			throw std::runtime_error("MasteringVoice create error");
		}

		m_assets = ComponentFrameworkProcessor::addClass(true, new SoundAssets());
	}

	SoundUpdater::~SoundUpdater()
	{
		m_assets.processingClassPtr().deletePtr();

		if (m_soundEvent != NULL)
			CloseHandle(m_soundEvent);

		if (m_masterVoicePtr != NULL)
			m_masterVoicePtr->DestroyVoice();

		if (m_xAudioPtr != NULL)
			m_xAudioPtr->Release();

		CoUninitialize();
	}

	void SoundUpdater::update()
	{
		DWORD dw = WaitForSingleObject(m_soundEvent, 0LU);

		if (dw == WAIT_OBJECT_0)
		{
			m_assets->updatePlayingSound();
		}
	}

	void SoundUpdater::load(int id, const std::string & fileName)
	{
		m_assets->load(id, fileName, m_xAudioPtr, m_soundEvent);
	}

	void SoundUpdater::play(int id, bool loopPlay)
	{
		SoundData* playSoundData = m_assets->getDataPtr(id);

		if (!playSoundData->isPlaySound())
		{
			playSoundData->playSound(loopPlay);
		}
	}

	void SoundUpdater::stop(int id)
	{
		SoundData* stopSoundData = m_assets->getDataPtr(id);

		if (stopSoundData->isPlaySound())
		{
			stopSoundData->stopSound();
		}
	}

	void SoundUpdater::pause(int id)
	{
		SoundData* pauseSoundData = m_assets->getDataPtr(id);

		if (pauseSoundData->isPlaySound())
		{
			pauseSoundData->pauseSound();
		}
	}

	void SoundUpdater::setMasterVolume(float volume)
	{
		volume = MathHelper::clamp(volume, 0.0f, 1.0f);

		m_masterVoicePtr->SetVolume(volume);
	}
}