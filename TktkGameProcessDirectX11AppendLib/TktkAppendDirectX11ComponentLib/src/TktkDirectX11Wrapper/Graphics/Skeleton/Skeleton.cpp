#include "TktkDirectX11Wrapper/Graphics/Skeleton/Skeleton.h"

#include <stdexcept>
#include "TktkDirectX11Wrapper/Graphics/Skeleton/SkeletonManager.h"

namespace tktk
{
	void Skeleton::create(int id, const std::vector<Bone>& boneArray)
	{
		if (id <= 0)
		{
			throw std::runtime_error("SkeletonId Fraud Value");
		}
		SkeletonManager::create(id, boneArray);
	}

	void Skeleton::erase(int id)
	{
		if (id <= 0)
		{
			throw std::runtime_error("SkeletonId Fraud Value");
		}
		SkeletonManager::erase(id);
	}

	const SkeletonData & Skeleton::getData(int id)
	{
		return SkeletonManager::getData(id);
	}
}