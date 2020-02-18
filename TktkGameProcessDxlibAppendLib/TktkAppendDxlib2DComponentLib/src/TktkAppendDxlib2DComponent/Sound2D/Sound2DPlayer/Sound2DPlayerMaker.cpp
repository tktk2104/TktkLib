#include "TktkAppendDxlib2DComponent/Sound2D/Sound2DPlayer/Sound2DPlayerMaker.h"

namespace tktk
{
	Sound2DPlayerMaker Sound2DPlayerMaker::m_self;

	Sound2DPlayerMaker & Sound2DPlayerMaker::makeStart()
	{
		m_self = Sound2DPlayerMaker();
		return m_self;
	}

	std::shared_ptr<Sound2DPlayer> Sound2DPlayerMaker::create()
	{
		return std::make_shared<Sound2DPlayer>(
			m_startToPlay,
			m_playSoundId,
			m_soundPlayType,
			m_playFromTop,
			m_useDefaltPanPalRate,
			m_useDefaltVolumeRate,
			m_panPalRate,
			m_volumeRate
			);
	}

	Sound2DPlayerMaker & Sound2DPlayerMaker::startToPlay(bool value)
	{
		m_startToPlay = value;
		return *this;
	}

	Sound2DPlayerMaker & Sound2DPlayerMaker::playSoundId(int value)
	{
		m_playSoundId = value;
		return *this;
	}

	Sound2DPlayerMaker & Sound2DPlayerMaker::soundPlayType(SoundPlayType value)
	{
		m_soundPlayType = value;
		return *this;
	}

	Sound2DPlayerMaker & Sound2DPlayerMaker::playFromTop(bool value)
	{
		m_playFromTop = value;
		return *this;
	}

	Sound2DPlayerMaker & Sound2DPlayerMaker::panPalRate(float value)
	{
		m_useDefaltPanPalRate = false;
		m_panPalRate = value;
		return *this;
	}

	Sound2DPlayerMaker & Sound2DPlayerMaker::volumeRate(float value)
	{
		m_useDefaltVolumeRate = false;
		m_volumeRate = value;
		return *this;
	}
}