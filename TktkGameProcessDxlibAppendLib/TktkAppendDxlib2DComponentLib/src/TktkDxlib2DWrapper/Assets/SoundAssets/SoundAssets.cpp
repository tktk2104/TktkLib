#include "TktkDxlib2DWrapper/Assets/SoundAssets/SoundAssets.h"

#include <stdexcept>
#include <algorithm>
#include <DxLib.h>

namespace tktk
{
	void SoundAssets::onDestroy() const
	{
		std::for_each(
			std::begin(m_soundAssetsMap),
			std::end(m_soundAssetsMap),
			[](const auto& node) { DxLib::DeleteSoundMem(node.second); }
		);
	}

	void SoundAssets::loadSound(int id, const std::string & assetFilePath, float pitchRate, float timeStretchRate, bool sound3d)
	{
		eraseSound(id);

		DxLib::SetCreate3DSoundFlag((sound3d) ? TRUE : FALSE);

		DxLib::SetCreateSoundPitchRate(pitchRate);

		DxLib::SetCreateSoundTimeStretchRate(timeStretchRate);

		int soundHandle = DxLib::LoadSoundMem(assetFilePath.c_str(), 1);

		m_soundAssetsMap.insert(std::make_pair(id, soundHandle));
	}

	void SoundAssets::duplicateSound(int id, int originalSoundId)
	{
		eraseSound(id);

		auto originalSoundHandleItr = m_soundAssetsMap.find(originalSoundId);

		if (originalSoundHandleItr == std::end(m_soundAssetsMap))
		{
			throw std::runtime_error("originalSoundId not found");
		}
		int soundHandle = DxLib::DuplicateSoundMem((*originalSoundHandleItr).second);

		m_soundAssetsMap.insert(std::make_pair(id, soundHandle));
	}

	void SoundAssets::eraseSound(int id)
	{
		auto eraseNode = m_soundAssetsMap.find(id);
		if (eraseNode == std::end(m_soundAssetsMap)) return;

		DxLib::DeleteSoundMem((*eraseNode).second);
		m_soundAssetsMap.erase(id);
	}

	void SoundAssets::eraseSoundAll()
	{
		std::for_each(
			std::begin(m_soundAssetsMap),
			std::end(m_soundAssetsMap),
			[](const auto& node) { DxLib::DeleteSoundMem(node.second); }
		);
		m_soundAssetsMap.clear();
	}

	int SoundAssets::getSoundHandle(int id) const
	{
		return m_soundAssetsMap.at(id);
	}
}