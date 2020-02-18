#include "TktkAppendDxlib2DComponent/Sound2D/Sound2DPlayer/Sound2DPlayer.h"

#include "TktkDxlib2DWrapper/Sound2D/Sound2DManager.h"

namespace tktk
{
	Sound2DPlayer::Sound2DPlayer(
		bool startToPlay,
		int playSoundId,
		SoundPlayType soundPlayType,
		bool playFromTop,
		bool useDefaltPanPalRate,
		bool useDefaltVolumeRate,
		float panPalRate,
		float volumeRate
	)
		: m_startToPlay(startToPlay)
		, m_playSoundId(playSoundId)
		, m_soundPlayType(soundPlayType)
		, m_playFromTop(playFromTop)
		, m_useDefaltPanPalRate(useDefaltPanPalRate)
		, m_useDefaltVolumeRate(useDefaltVolumeRate)
		, m_panPalRate(panPalRate)
		, m_volumeRate(volumeRate)
	{
	}

	void Sound2DPlayer::start()
	{
		if (m_startToPlay) playSound();
	}

	void Sound2DPlayer::playSound()
	{
		if (!m_useDefaltPanPalRate) Sound2DManager::changeNextPan(m_playSoundId, m_panPalRate);
		if (!m_useDefaltVolumeRate) Sound2DManager::changeNextVolume(m_playSoundId, m_volumeRate);

		Sound2DManager::playSound(m_playSoundId, m_soundPlayType, m_playFromTop);
	}

	void Sound2DPlayer::stopSound()
	{
		Sound2DManager::stopSound(m_playSoundId);
	}

	bool Sound2DPlayer::isPlaySound()
	{
		return Sound2DManager::isPlaySound(m_playSoundId);
	}

	void Sound2DPlayer::setPlaySoundId(int playSoundId)
	{
		m_playSoundId = playSoundId;
	}

	void Sound2DPlayer::setSoundPlayType(SoundPlayType soundPlayType)
	{
		m_soundPlayType = soundPlayType;
	}

	void Sound2DPlayer::setPlayFromTop(bool playFromTop)
	{
		m_playFromTop = playFromTop;
	}

	void Sound2DPlayer::setPanPalRate(float panPalRate)
	{
		m_useDefaltPanPalRate = false;
		m_panPalRate = panPalRate;
	}

	void Sound2DPlayer::useDefaltPanPalRate()
	{
		m_useDefaltPanPalRate = true;
	}

	void Sound2DPlayer::setVolumeRate(float volumeRate)
	{
		m_useDefaltVolumeRate = false;
		m_volumeRate = volumeRate;
	}

	void Sound2DPlayer::useDefaltVolumeRate()
	{
		m_useDefaltVolumeRate = true;
	}
}