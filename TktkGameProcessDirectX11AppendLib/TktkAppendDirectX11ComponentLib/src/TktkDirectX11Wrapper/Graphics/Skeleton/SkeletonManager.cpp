#include "TktkDirectX11Wrapper/Graphics/Skeleton/SkeletonManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	CfpPtr<SkeletonAssets> SkeletonManager::m_assetsPtr;

	void SkeletonManager::setUp()
	{
		m_assetsPtr = ComponentFrameworkProcessor::addClass(true, new SkeletonAssets());
	}

	void SkeletonManager::clear()
	{
		m_assetsPtr->clear();
	}

	void SkeletonManager::createImpl(int id, const std::vector<Bone>& boneArray)
	{
		m_assetsPtr->create(id, boneArray);
	}

	void SkeletonManager::eraseImpl(int id)
	{
		m_assetsPtr->erase(id);
	}

	const SkeletonData & SkeletonManager::getDataImpl(int id)
	{
		return m_assetsPtr->getData(id);
	}
}