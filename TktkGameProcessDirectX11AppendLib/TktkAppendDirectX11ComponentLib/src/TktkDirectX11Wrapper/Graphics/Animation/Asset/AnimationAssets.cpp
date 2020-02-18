#include "TktkDirectX11Wrapper/Graphics/Animation/Asset/AnimationAssets.h"

namespace tktk
{
	AnimationAssets::~AnimationAssets()
	{
		clear();
	}

	void AnimationAssets::create(int id, const std::unordered_map<std::string, std::vector<KeyFrame>>& boneKeyFrames)
	{
		erase(id);

		m_assets.emplace(
			std::piecewise_construct,
			std::forward_as_tuple(id),
			std::forward_as_tuple(boneKeyFrames)
		);
	}

	void AnimationAssets::erase(int id)
	{
		auto eraseNode = m_assets.find(id);
		if (eraseNode == std::end(m_assets)) return;
		m_assets.erase(id);
	}

	void AnimationAssets::clear()
	{
		m_assets.clear();
	}

	const AnimationData & AnimationAssets::getData(int id) const
	{
		return m_assets.at(id);
	}
}