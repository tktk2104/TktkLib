#include "TktkAppendDxlib3DComponent/Sound3D/Sound3DPlayer/Sound3DPlayer.h"

#include "TktkDxlib3DWrapper/Sound3D/Sound3DManager.h"

namespace tktk
{
	Sound3DPlayer::Sound3DPlayer(
		bool startToPlay,
		int playSoundId,
		SoundPlayType soundPlayType,
		bool playFromTop,
		bool useDefaltPlayRadius,
		bool useDefaltPlayVelocity,
		bool useDefaltVolumeRate,
		float playRadius,
		const Vector3 & playVelocity,
		float volumeRate
	)
		: m_startToPlay(startToPlay)
		, m_playSoundId(playSoundId)
		, m_soundPlayType(soundPlayType)
		, m_playFromTop(playFromTop)
		, m_useDefaltPlayRadius(useDefaltPlayRadius)
		, m_useDefaltPlayVelocity(useDefaltPlayVelocity)
		, m_useDefaltVolumeRate(useDefaltVolumeRate)
		, m_playRadius(playRadius)
		, m_playVelocity(playVelocity)
		, m_volumeRate(volumeRate)
	{
	}

	void Sound3DPlayer::start()
	{
		auto transform3D = getComponent<Transform3D>();

		if (transform3D.expired())
		{
			throw std::runtime_error("Sound3DPlayer not found Transform3D");
		}
		m_transform3D = transform3D;

		if (m_startToPlay) playSound();
	}

	void Sound3DPlayer::update()
	{
		Sound3DManager::changePlayPosition(m_playSoundId, m_transform3D.lock()->getWorldPosition());
	}

	void Sound3DPlayer::onDestroy() const
	{
		Sound3DManager::stopSound(m_playSoundId);
	}

	void Sound3DPlayer::playSound()
	{
		if (!m_useDefaltPlayRadius) Sound3DManager::changeNextPlayRadius(m_playSoundId, m_playRadius);
		if (!m_useDefaltPlayVelocity) Sound3DManager::changeNextPlayVelocity(m_playSoundId, m_playVelocity);
		if (!m_useDefaltVolumeRate) Sound3DManager::changeNextVolume(m_playSoundId, m_volumeRate);

		Sound3DManager::playSound(m_playSoundId, m_soundPlayType, m_playFromTop);
	}

	void Sound3DPlayer::stopSound()
	{
		Sound3DManager::stopSound(m_playSoundId);
	}

	bool Sound3DPlayer::isPlaySound()
	{
		return Sound3DManager::isPlaySound(m_playSoundId);
	}

	void Sound3DPlayer::setPlaySoundId(int playSoundId)
	{
		m_playSoundId = playSoundId;
	}

	void Sound3DPlayer::setSoundPlayType(SoundPlayType soundPlayType)
	{
		m_soundPlayType = soundPlayType;
	}

	void Sound3DPlayer::setPlayFromTop(bool playFromTop)
	{
		m_playFromTop = playFromTop;
	}

	void Sound3DPlayer::setPlayRadius(float playRadius)
	{
		m_useDefaltPlayRadius = false;
		m_playRadius = playRadius;
	}

	void Sound3DPlayer::useDefaltPlayRadius()
	{
		m_useDefaltPlayRadius = true;
	}

	void Sound3DPlayer::setPlayVelocity(const Vector3 & playVelocity)
	{
		m_useDefaltPlayVelocity = false;
		m_playVelocity = playVelocity;
	}

	void Sound3DPlayer::useDefaltPlayVelocity()
	{
		m_useDefaltPlayVelocity = true;
	}

	void Sound3DPlayer::setVolumeRate(float volumeRate)
	{
		m_useDefaltVolumeRate = false;
		m_volumeRate = volumeRate;
	}

	void Sound3DPlayer::useDefaltVolumeRate()
	{
		m_useDefaltVolumeRate = true;
	}
}