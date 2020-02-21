#include "TktkDxlib2DWrapper/Sound2D/Sound2DManager.h"

#include <stdexcept>
#include <DxLib.h>
#include "TktkDxlib2DWrapper/Assets/Assets2DManager.h"

namespace tktk
{
	void Sound2DManager::playSound(int id, SoundPlayType soundPlayType, bool topPositionFlag)
	{
		DxLib::PlaySoundMem(Assets2DManager::getSoundAssets()->getSoundHandle(id), soundPlayType, (topPositionFlag) ? TRUE : FALSE);
	}

	void Sound2DManager::stopSound(int id)
	{
		DxLib::StopSoundMem(Assets2DManager::getSoundAssets()->getSoundHandle(id));
	}

	bool Sound2DManager::isPlaySound(int id)
	{
		return (DxLib::CheckSoundMem(Assets2DManager::getSoundAssets()->getSoundHandle(id)) == TRUE);
	}

	void Sound2DManager::changePan(int id, float panPalRate)
	{
		DxLib::ChangePanSoundMem(static_cast<int>(panPalRate * 255), Assets2DManager::getSoundAssets()->getSoundHandle(id));
	}

	void Sound2DManager::changeNextPan(int id, float panPalRate)
	{
		DxLib::ChangeNextPlayPanSoundMem(static_cast<int>(panPalRate * 255), Assets2DManager::getSoundAssets()->getSoundHandle(id));
	}

	void Sound2DManager::changeVolume(int id, float volumeRate)
	{
		DxLib::ChangeVolumeSoundMem(static_cast<int>(volumeRate * 255), Assets2DManager::getSoundAssets()->getSoundHandle(id));
	}

	void Sound2DManager::changeNextVolume(int id, float volumeRate)
	{
		DxLib::ChangeNextPlayVolumeSoundMem(static_cast<int>(volumeRate * 255), Assets2DManager::getSoundAssets()->getSoundHandle(id));
	}

	void Sound2DManager::setFrequency(int id, int frequencyPalHz)
	{
		DxLib::SetFrequencySoundMem(frequencyPalHz, Assets2DManager::getSoundAssets()->getSoundHandle(id));
	}

	void Sound2DManager::setLoopPos(int id, float loopTimeSec)
	{
		DxLib::SetLoopPosSoundMem(static_cast<int>(loopTimeSec * 1000), Assets2DManager::getSoundAssets()->getSoundHandle(id));
	}

	void Sound2DManager::setLoopSamplePos(int id, int loopSamplePosition)
	{
		DxLib::SetLoopSamplePosSoundMem(loopSamplePosition, Assets2DManager::getSoundAssets()->getSoundHandle(id));
	}

	void Sound2DManager::setCurrentPosition(int id, int samplePosition)
	{
		DxLib::SetCurrentPositionSoundMem(samplePosition, Assets2DManager::getSoundAssets()->getSoundHandle(id));
	}
}