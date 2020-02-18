#include "TktkDirectX11Wrapper/Graphics/Skeleton/Asset/SkeletonAssets.h"

namespace tktk
{
	SkeletonAssets::~SkeletonAssets()
	{
		clear();
	}

	void SkeletonAssets::create(int id, const std::vector<Bone>& boneArray)
	{
		erase(id);

		m_assets.emplace(
			std::piecewise_construct,
			std::forward_as_tuple(id),
			std::forward_as_tuple(boneArray)
		);
	}

	void SkeletonAssets::erase(int id)
	{
		auto eraseNode = m_assets.find(id);
		if (eraseNode == std::end(m_assets)) return;
		m_assets.erase(id);
	}

	void SkeletonAssets::clear()
	{
		m_assets.clear();
	}

	const SkeletonData & SkeletonAssets::getData(int id) const
	{
		return m_assets.at(id);
	}
}