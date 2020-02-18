#include "TktkDirectX11Wrapper/Graphics/Animation/AnimationManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	CfpPtr<AnimationAssets> AnimationManager::m_assetsPtr;

	void AnimationManager::setUp()
	{
		m_assetsPtr = ComponentFrameworkProcessor::addClass(true, new AnimationAssets());
	}

	void AnimationManager::create(int id, const std::unordered_map<std::string, std::vector<KeyFrame>>& boneKeyFrames)
	{
		m_assetsPtr->create(id, boneKeyFrames);
	}

	void AnimationManager::erase(int id)
	{
		m_assetsPtr->erase(id);
	}

	void AnimationManager::clear()
	{
		m_assetsPtr->clear();
	}

	const AnimationData & AnimationManager::getData(int id)
	{
		return m_assetsPtr->getData(id);
	}
}