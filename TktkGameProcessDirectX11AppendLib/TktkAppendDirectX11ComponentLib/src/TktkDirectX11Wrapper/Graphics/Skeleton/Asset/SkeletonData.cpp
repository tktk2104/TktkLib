#include "TktkDirectX11Wrapper/Graphics/Skeleton/Asset/SkeletonData.h"

namespace tktk
{
	SkeletonData::SkeletonData(const std::vector<Bone>& boneArray)
		: m_boneArray(boneArray)
	{
	}

	SkeletonData::~SkeletonData()
	{
	}

	unsigned int SkeletonData::getSize() const
	{
		return m_boneArray.size();
	}

	const std::vector<Bone>& SkeletonData::getBoneArray() const
	{
		return m_boneArray;
	}
}