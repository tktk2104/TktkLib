#include "TktkDxlib2DWrapper/Sound2D/Sound2DManager.h"

#include <stdexcept>
#include <DxLib.h>
#include "TktkDxlib2DWrapper/Assets/Assets2DManager.h"

namespace tktk
{
	std::weak_ptr<SoundAssets> Sound2DManager::m_soundAssets;

	void Sound2DManager::setUp()
	{
		auto soundAssets = Assets2DManager::getSoundAssets();

		if (soundAssets.expired())
		{
			throw std::runtime_error("SoundManager not found SoundAssets");
		}
		m_soundAssets = soundAssets;
	}

	void Sound2DManager::playSound(int id, SoundPlayType soundPlayType, bool topPositionFlag)
	{
		DxLib::PlaySoundMem(m_soundAssets.lock()->getSoundHandle(id), soundPlayType, (topPositionFlag) ? TRUE : FALSE);
	}

	void Sound2DManager::stopSound(int id)
	{
		DxLib::StopSoundMem(m_soundAssets.lock()->getSoundHandle(id));
	}

	bool Sound2DManager::isPlaySound(int id)
	{
		return (DxLib::CheckSoundMem(m_soundAssets.lock()->getSoundHandle(id)) == TRUE);
	}

	void Sound2DManager::changePan(int id, float panPalRate)
	{
		DxLib::ChangePanSoundMem(static_cast<int>(panPalRate * 255), m_soundAssets.lock()->getSoundHandle(id));
	}

	void Sound2DManager::changeNextPan(int id, float panPalRate)
	{
		DxLib::ChangeNextPlayPanSoundMem(static_cast<int>(panPalRate * 255), m_soundAssets.lock()->getSoundHandle(id));
	}

	void Sound2DManager::changeVolume(int id, float volumeRate)
	{
		DxLib::ChangeVolumeSoundMem(static_cast<int>(volumeRate * 255), m_soundAssets.lock()->getSoundHandle(id));
	}

	void Sound2DManager::changeNextVolume(int id, float volumeRate)
	{
		DxLib::ChangeNextPlayVolumeSoundMem(static_cast<int>(volumeRate * 255), m_soundAssets.lock()->getSoundHandle(id));
	}

	void Sound2DManager::setFrequency(int id, int frequencyPalHz)
	{
		DxLib::SetFrequencySoundMem(frequencyPalHz, m_soundAssets.lock()->getSoundHandle(id));
	}

	void Sound2DManager::setLoopPos(int id, float loopTimeSec)
	{
		DxLib::SetLoopPosSoundMem(static_cast<int>(loopTimeSec * 1000), m_soundAssets.lock()->getSoundHandle(id));
	}

	void Sound2DManager::setLoopSamplePos(int id, int loopSamplePosition)
	{
		DxLib::SetLoopSamplePosSoundMem(loopSamplePosition, m_soundAssets.lock()->getSoundHandle(id));
	}

	void Sound2DManager::setCurrentPosition(int id, int samplePosition)
	{
		DxLib::SetCurrentPositionSoundMem(samplePosition, m_soundAssets.lock()->getSoundHandle(id));
	}
}