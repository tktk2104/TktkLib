#include "TktkDirectX11Wrapper/Sound/Asset/SoundAssets.h"

#include <algorithm>

namespace tktk
{
	inline void updatePlayingSoundImpl(SoundData& updateSound);

	SoundAssets::~SoundAssets()
	{
		clear();
	}

	void SoundAssets::load(int id, const std::string & fileName, IXAudio2* xAudioPtr, HANDLE hEvent)
	{
		erase(id);

		m_assets.emplace(
			std::piecewise_construct,
			std::forward_as_tuple(id),
			std::forward_as_tuple(fileName, xAudioPtr, hEvent)
		);
	}

	void SoundAssets::erase(int id)
	{
		auto eraseNode = m_assets.find(id);
		if (eraseNode == std::end(m_assets)) return;
		m_assets.erase(id);
	}

	void SoundAssets::clear()
	{
		m_assets.clear();
	}

	void SoundAssets::updatePlayingSound()
	{
		std::for_each(
			std::begin(m_assets),
			std::end(m_assets),
			[](auto& node) { updatePlayingSoundImpl(node.second); }
		);
	}

	SoundData * SoundAssets::getDataPtr(int id)
	{
		return &(m_assets.at(id));
	}

	void updatePlayingSoundImpl(SoundData& updateSound)
	{
		if (updateSound.isPlaySound()) updateSound.update();
	}
}