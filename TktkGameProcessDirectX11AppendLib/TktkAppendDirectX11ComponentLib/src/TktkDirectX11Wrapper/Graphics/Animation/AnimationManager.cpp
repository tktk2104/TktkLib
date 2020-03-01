#include "TktkDirectX11Wrapper/Graphics/Animation/AnimationManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	CfpPtr<AnimationAssets> AnimationManager::m_assetsPtr;

	void AnimationManager::setUp()
	{
		m_assetsPtr = ComponentFrameworkProcessor::addClass(true, new AnimationAssets());
	}

	void AnimationManager::clear()
	{
		m_assetsPtr->clear();
	}

	void AnimationManager::createImpl(int id, const std::unordered_map<std::string, std::vector<KeyFrame>>& boneKeyFrames)
	{
		m_assetsPtr->create(id, boneKeyFrames);
	}

	void AnimationManager::eraseImpl(int id)
	{
		m_assetsPtr->erase(id);
	}

	

	const AnimationData & AnimationManager::getDataImpl(int id)
	{
		return m_assetsPtr->getData(id);
	}
}