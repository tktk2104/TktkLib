#include "TktkDxlib3DWrapper/Sound3D/Sound3DManager.h"

#include <stdexcept>
#include <DxLib.h>
#include <TktkDxlib2DWrapper/Utility/DXConverter.h>
#include <TktkDxlib2DWrapper/Assets/Assets2DManager.h>

namespace tktk
{
	std::weak_ptr<SoundAssets> Sound3DManager::m_soundAssets;

	void Sound3DManager::setUp()
	{
		auto soundAssets = Assets2DManager::getSoundAssets();

		if (soundAssets.expired())
		{
			throw std::runtime_error("SoundManager not found SoundAssets");
		}
		m_soundAssets = soundAssets;
	}

	void Sound3DManager::playSound(int id, SoundPlayType soundPlayType, bool topPositionFlag)
	{
		DxLib::PlaySoundMem(m_soundAssets.lock()->getSoundHandle(id), soundPlayType, (topPositionFlag) ? TRUE : FALSE);
	}

	void Sound3DManager::stopSound(int id)
	{
		DxLib::StopSoundMem(m_soundAssets.lock()->getSoundHandle(id));
	}

	bool Sound3DManager::isPlaySound(int id)
	{
		return (DxLib::CheckSoundMem(m_soundAssets.lock()->getSoundHandle(id)) == TRUE);
	}

	void Sound3DManager::changePlayPosition(int id, const Vector3 & playPos)
	{
		DxLib::Set3DPositionSoundMem(DXConverter::toVECTOR(playPos), m_soundAssets.lock()->getSoundHandle(id));
	}

	void Sound3DManager::changeNextPlayPosition(int id, const Vector3 & playPos)
	{
		DxLib::SetNextPlay3DPositionSoundMem(DXConverter::toVECTOR(playPos), m_soundAssets.lock()->getSoundHandle(id));
	}

	void Sound3DManager::changePlayRadius(int id, float playRadius)
	{
		DxLib::Set3DRadiusSoundMem(playRadius, m_soundAssets.lock()->getSoundHandle(id));
	}

	void Sound3DManager::changeNextPlayRadius(int id, float playRadius)
	{
		DxLib::SetNextPlay3DRadiusSoundMem(playRadius, m_soundAssets.lock()->getSoundHandle(id));
	}

	void Sound3DManager::changePlayVelocity(int id, const Vector3 & velocity)
	{
		DxLib::Set3DVelocitySoundMem(DXConverter::toVECTOR(velocity), m_soundAssets.lock()->getSoundHandle(id));
	}

	void Sound3DManager::changeNextPlayVelocity(int id, const Vector3 & velocity)
	{
		DxLib::SetNextPlay3DVelocitySoundMem(DXConverter::toVECTOR(velocity), m_soundAssets.lock()->getSoundHandle(id));
	}

	void Sound3DManager::changeVolume(int id, float volumeRate)
	{
		DxLib::ChangeVolumeSoundMem(static_cast<int>(volumeRate * 255), m_soundAssets.lock()->getSoundHandle(id));
	}

	void Sound3DManager::changeNextVolume(int id, float volumeRate)
	{
		DxLib::ChangeNextPlayVolumeSoundMem(static_cast<int>(volumeRate * 255), m_soundAssets.lock()->getSoundHandle(id));
	}

	void Sound3DManager::setFrequency(int id, int frequencyPalHz)
	{
		DxLib::SetFrequencySoundMem(frequencyPalHz, m_soundAssets.lock()->getSoundHandle(id));
	}

	void Sound3DManager::setLoopPos(int id, float loopTimeSec)
	{
		DxLib::SetLoopPosSoundMem(static_cast<int>(loopTimeSec * 1000), m_soundAssets.lock()->getSoundHandle(id));
	}

	void Sound3DManager::setLoopSamplePos(int id, int loopSamplePosition)
	{
		DxLib::SetLoopSamplePosSoundMem(loopSamplePosition, m_soundAssets.lock()->getSoundHandle(id));
	}

	void Sound3DManager::setCurrentPosition(int id, int samplePosition)
	{
		DxLib::SetCurrentPositionSoundMem(samplePosition, m_soundAssets.lock()->getSoundHandle(id));
	}

	void Sound3DManager::setSoundListenerPosition(const Vector3 & pos, const Vector3 & front, const Vector3 & up)
	{
		DxLib::Set3DSoundListenerPosAndFrontPosAndUpVec(
			DXConverter::toVECTOR(pos),
			DXConverter::toVECTOR(pos + front),
			DXConverter::toVECTOR(up)
		);

	}
}