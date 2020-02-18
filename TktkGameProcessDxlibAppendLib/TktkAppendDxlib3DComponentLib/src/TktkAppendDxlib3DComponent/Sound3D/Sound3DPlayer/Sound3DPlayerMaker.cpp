#include "TktkAppendDxlib3DComponent/Sound3D/Sound3DPlayer/Sound3DPlayerMaker.h"

namespace tktk
{
	Sound3DPlayerMaker Sound3DPlayerMaker::m_self;

	Sound3DPlayerMaker & Sound3DPlayerMaker::makeStart()
	{
		m_self = Sound3DPlayerMaker();
		return m_self;
	}

	std::shared_ptr<Sound3DPlayer> Sound3DPlayerMaker::create()
	{
		return std::make_shared<Sound3DPlayer>(
			m_startToPlay,
			m_playSoundId,
			m_soundPlayType,
			m_playFromTop,
			m_useDefaltPlayRadius,
			m_useDefaltPlayVelocity,
			m_useDefaltVolumeRate,
			m_playRadius,
			m_playVelocity,
			m_volumeRate
			);
	}

	Sound3DPlayerMaker & Sound3DPlayerMaker::startToPlay(bool value)
	{
		m_startToPlay = value;
		return *this;
	}

	Sound3DPlayerMaker & Sound3DPlayerMaker::playSoundId(int value)
	{
		m_playSoundId = value;
		return *this;
	}

	Sound3DPlayerMaker & Sound3DPlayerMaker::soundPlayType(SoundPlayType value)
	{
		m_soundPlayType = value;
		return *this;
	}

	Sound3DPlayerMaker & Sound3DPlayerMaker::playFromTop(bool value)
	{
		m_playFromTop = value;
		return *this;
	}

	Sound3DPlayerMaker & Sound3DPlayerMaker::playRadius(float value)
	{
		m_useDefaltPlayRadius = false;
		m_playRadius = value;
		return *this;
	}

	Sound3DPlayerMaker & Sound3DPlayerMaker::playVelocity(const Vector3 & value)
	{
		m_useDefaltPlayVelocity = false;
		m_playVelocity = value;
		return *this;
	}

	Sound3DPlayerMaker & Sound3DPlayerMaker::volumeRate(float value)
	{
		m_useDefaltVolumeRate = false;
		m_volumeRate = value;
		return *this;
	}
}