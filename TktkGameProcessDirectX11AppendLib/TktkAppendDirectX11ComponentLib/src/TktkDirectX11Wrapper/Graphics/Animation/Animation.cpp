#include "TktkDirectX11Wrapper/Graphics/Animation/Animation.h"

#include <stdexcept>
#include "TktkDirectX11Wrapper/Graphics/Animation/AnimationManager.h"

namespace tktk
{
	void Animation::createImpl(int id, const std::unordered_map<std::string, std::vector<KeyFrame>>& boneKeyFrames)
	{
		if (id <= 0)
		{
			throw std::runtime_error("AnimationId Fraud Value");
		}
		AnimationManager::create(id, boneKeyFrames);
	}

	void Animation::eraseImpl(int id)
	{
		if (id <= 0)
		{
			throw std::runtime_error("AnimationId Fraud Value");
		}
		AnimationManager::erase(id);
	}

	const AnimationData & Animation::getDataImpl(int id)
	{
		return AnimationManager::getData(id);
	}
}