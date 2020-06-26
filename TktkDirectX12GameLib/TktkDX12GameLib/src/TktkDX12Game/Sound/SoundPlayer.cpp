#include "TktkDX12Game/Sound/SoundPlayer.h"

#include <stdexcept>
#include <TktkMath/MathHelper.h>

namespace tktk
{
	SoundPlayer::SoundPlayer(unsigned int soundDataNum)
		: m_sound(soundDataNum)
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

	SoundPlayer::~SoundPlayer()
	{
		if (m_soundEvent != NULL)
			CloseHandle(m_soundEvent);

		if (m_masterVoicePtr != NULL)
			m_masterVoicePtr->DestroyVoice();

		if (m_xAudioPtr != NULL)
			m_xAudioPtr->Release();

		CoUninitialize();
	}

	void SoundPlayer::finalize()
	{
		m_sound.clear();
	}

	void SoundPlayer::update()
	{
		DWORD dw = WaitForSingleObject(m_soundEvent, 0LU);

		if (dw == WAIT_OBJECT_0)
		{
			m_sound.updatePlayingSound();
		}
	}

	void SoundPlayer::load(unsigned int id, const std::string & fileName)
	{
		m_sound.load(id, fileName, m_xAudioPtr, m_soundEvent);
	}

	void SoundPlayer::play(unsigned int id, bool loopPlay)
	{
		m_sound.play(id, loopPlay);
	}

	void SoundPlayer::stop(unsigned int id)
	{
		m_sound.stop(id);
	}

	void SoundPlayer::pause(unsigned int id)
	{
		m_sound.pause(id);
	}

	void SoundPlayer::setMasterVolume(float volume)
	{
		volume = tktkMath::MathHelper::clamp(volume, 0.0f, 1.0f);

		m_masterVoicePtr->SetVolume(volume);
	}
}