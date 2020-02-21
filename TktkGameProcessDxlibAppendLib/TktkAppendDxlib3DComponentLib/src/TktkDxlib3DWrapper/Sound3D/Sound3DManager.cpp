#include "TktkDxlib3DWrapper/Sound3D/Sound3DManager.h"

#include <stdexcept>
#include <DxLib.h>
#include <TktkDxlib2DWrapper/Utility/DXConverter.h>
#include <TktkDxlib2DWrapper/Assets/Assets2DManager.h>

namespace tktk
{

	void Sound3DManager::playSound(int id, SoundPlayType soundPlayType, bool topPositionFlag)
	{
		DxLib::PlaySoundMem(Assets2DManager::getSoundAssets()->getSoundHandle(id), soundPlayType, (topPositionFlag) ? TRUE : FALSE);
	}

	void Sound3DManager::stopSound(int id)
	{
		DxLib::StopSoundMem(Assets2DManager::getSoundAssets()->getSoundHandle(id));
	}

	bool Sound3DManager::isPlaySound(int id)
	{
		return (DxLib::CheckSoundMem(Assets2DManager::getSoundAssets()->getSoundHandle(id)) == TRUE);
	}

	void Sound3DManager::changePlayPosition(int id, const Vector3 & playPos)
	{
		DxLib::Set3DPositionSoundMem(DXConverter::toVECTOR(playPos), Assets2DManager::getSoundAssets()->getSoundHandle(id));
	}

	void Sound3DManager::changeNextPlayPosition(int id, const Vector3 & playPos)
	{
		DxLib::SetNextPlay3DPositionSoundMem(DXConverter::toVECTOR(playPos), Assets2DManager::getSoundAssets()->getSoundHandle(id));
	}

	void Sound3DManager::changePlayRadius(int id, float playRadius)
	{
		DxLib::Set3DRadiusSoundMem(playRadius, Assets2DManager::getSoundAssets()->getSoundHandle(id));
	}

	void Sound3DManager::changeNextPlayRadius(int id, float playRadius)
	{
		DxLib::SetNextPlay3DRadiusSoundMem(playRadius, Assets2DManager::getSoundAssets()->getSoundHandle(id));
	}

	void Sound3DManager::changePlayVelocity(int id, const Vector3 & velocity)
	{
		DxLib::Set3DVelocitySoundMem(DXConverter::toVECTOR(velocity), Assets2DManager::getSoundAssets()->getSoundHandle(id));
	}

	void Sound3DManager::changeNextPlayVelocity(int id, const Vector3 & velocity)
	{
		DxLib::SetNextPlay3DVelocitySoundMem(DXConverter::toVECTOR(velocity), Assets2DManager::getSoundAssets()->getSoundHandle(id));
	}

	void Sound3DManager::changeVolume(int id, float volumeRate)
	{
		DxLib::ChangeVolumeSoundMem(static_cast<int>(volumeRate * 255), Assets2DManager::getSoundAssets()->getSoundHandle(id));
	}

	void Sound3DManager::changeNextVolume(int id, float volumeRate)
	{
		DxLib::ChangeNextPlayVolumeSoundMem(static_cast<int>(volumeRate * 255), Assets2DManager::getSoundAssets()->getSoundHandle(id));
	}

	void Sound3DManager::setFrequency(int id, int frequencyPalHz)
	{
		DxLib::SetFrequencySoundMem(frequencyPalHz, Assets2DManager::getSoundAssets()->getSoundHandle(id));
	}

	void Sound3DManager::setLoopPos(int id, float loopTimeSec)
	{
		DxLib::SetLoopPosSoundMem(static_cast<int>(loopTimeSec * 1000), Assets2DManager::getSoundAssets()->getSoundHandle(id));
	}

	void Sound3DManager::setLoopSamplePos(int id, int loopSamplePosition)
	{
		DxLib::SetLoopSamplePosSoundMem(loopSamplePosition, Assets2DManager::getSoundAssets()->getSoundHandle(id));
	}

	void Sound3DManager::setCurrentPosition(int id, int samplePosition)
	{
		DxLib::SetCurrentPositionSoundMem(samplePosition, Assets2DManager::getSoundAssets()->getSoundHandle(id));
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