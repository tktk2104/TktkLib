#include "TktkDX12Game/DXGameResource/Sound/Sound.h"

#include <stdexcept>
#include <TktkMath/MathHelper.h>

namespace tktk
{
	Sound::Sound(unsigned int soundDataNum)
		: m_assets(soundDataNum)
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
	}

	Sound::~Sound()
	{
		if (m_soundEvent != NULL)
			CloseHandle(m_soundEvent);

		if (m_masterVoicePtr != NULL)
			m_masterVoicePtr->DestroyVoice();

		if (m_xAudioPtr != NULL)
			m_xAudioPtr->Release();

		CoUninitialize();
	}

	void Sound::update()
	{
		DWORD dw = WaitForSingleObject(m_soundEvent, 0LU);

		if (dw != WAIT_OBJECT_0) return;

		for (unsigned int i = 0; i < m_assets.arrayMaxSize(); i++)
		{
			auto ptr = m_assets.at(i);

			if (ptr != nullptr && ptr->isPlaySound()) ptr->update();
		}
	}

	void Sound::load(unsigned int id, const std::string& fileName)
	{
		m_assets.emplaceAt(id, fileName, m_xAudioPtr, m_soundEvent);
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

	void Sound::setMasterVolume(float volume)
	{
		volume = tktkMath::MathHelper::clamp(volume, 0.0f, 1.0f);

		m_masterVoicePtr->SetVolume(volume);
	}
}