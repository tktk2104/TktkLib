#include "TktkDxlib3DWrapper/Sound3D/Sound3D.h"

#include "TktkDxlib3DWrapper/Sound3D/Sound3DManager.h"

namespace tktk
{
	void Sound3D::playSound(int id, SoundPlayType soundPlayType, bool topPositionFlag)
	{
		Sound3DManager::playSound(id, soundPlayType, topPositionFlag);
	}

	void Sound3D::stopSound(int id)
	{
		Sound3DManager::stopSound(id);
	}

	bool Sound3D::isPlaySound(int id)
	{
		return Sound3DManager::isPlaySound(id);
	}

	void Sound3D::changePlayPosition(int id, const Vector3 & playPos)
	{
		Sound3DManager::changePlayPosition(id, playPos);
	}

	void Sound3D::changeNextPlayPosition(int id, const Vector3 & playPos)
	{
		Sound3DManager::changeNextPlayPosition(id, playPos);
	}

	void Sound3D::changePlayRadius(int id, float playRadius)
	{
		Sound3DManager::changePlayRadius(id, playRadius);
	}

	void Sound3D::changeNextPlayRadius(int id, float playRadius)
	{
		Sound3DManager::changeNextPlayRadius(id, playRadius);
	}

	void Sound3D::changePlayVelocity(int id, const Vector3 & velocity)
	{
		Sound3DManager::changePlayVelocity(id, velocity);
	}

	void Sound3D::changeNextPlayVelocity(int id, const Vector3 & velocity)
	{
		Sound3DManager::changeNextPlayVelocity(id, velocity);
	}

	void Sound3D::changeVolume(int id, float volumeRate)
	{
		Sound3DManager::changeVolume(id, volumeRate);
	}

	void Sound3D::changeNextVolume(int id, float volumeRate)
	{
		Sound3DManager::changeNextVolume(id, volumeRate);
	}

	void Sound3D::setFrequency(int id, int frequencyPalHz)
	{
		Sound3DManager::setFrequency(id, frequencyPalHz);
	}

	void Sound3D::setLoopPos(int id, float loopTimeSec)
	{
		Sound3DManager::setLoopPos(id, loopTimeSec);
	}

	void Sound3D::setLoopSamplePos(int id, int loopSamplePosition)
	{
		Sound3DManager::setLoopSamplePos(id, loopSamplePosition);
	}

	void Sound3D::setCurrentPosition(int id, int samplePosition)
	{
		Sound3DManager::setCurrentPosition(id, samplePosition);
	}

	void Sound3D::setSoundListenerPosition(const Vector3 & pos, const Vector3 & front, const Vector3 & up)
	{
		Sound3DManager::setSoundListenerPosition(pos, front, up);
	}
}