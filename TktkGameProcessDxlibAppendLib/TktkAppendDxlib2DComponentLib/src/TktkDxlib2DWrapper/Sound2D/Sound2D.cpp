#include "TktkDxlib2DWrapper/Sound2D/Sound2D.h"

#include "TktkDxlib2DWrapper/Sound2D/Sound2DManager.h"

namespace tktk
{
	void Sound2D::playSound(int id, SoundPlayType soundPlayType, bool topPositionFlag)
	{
		Sound2DManager::playSound(id, soundPlayType, topPositionFlag);
	}

	void Sound2D::stopSound(int id)
	{
		Sound2DManager::stopSound(id);
	}

	bool Sound2D::isPlaySound(int id)
	{
		return Sound2DManager::isPlaySound(id);
	}

	void Sound2D::changePan(int id, float panPalRate)
	{
		Sound2DManager::changePan(id, panPalRate);
	}

	void Sound2D::changeNextPan(int id, float panPalRate)
	{
		Sound2DManager::changeNextPan(id, panPalRate);
	}

	void Sound2D::changeVolume(int id, float volumeRate)
	{
		Sound2DManager::changeVolume(id, volumeRate);
	}

	void Sound2D::changeNextVolume(int id, float volumeRate)
	{
		Sound2DManager::changeNextVolume(id, volumeRate);
	}

	void Sound2D::setFrequency(int id, int frequencyPalHz)
	{
		Sound2DManager::setFrequency(id, frequencyPalHz);
	}

	void Sound2D::setLoopPos(int id, float loopTimeSec)
	{
		Sound2DManager::setLoopPos(id, loopTimeSec);
	}

	void Sound2D::setLoopSamplePos(int id, int loopSamplePosition)
	{
		Sound2DManager::setLoopSamplePos(id, loopSamplePosition);
	}

	void Sound2D::setCurrentPosition(int id, int samplePosition)
	{
		Sound2DManager::setCurrentPosition(id, samplePosition);
	}
}