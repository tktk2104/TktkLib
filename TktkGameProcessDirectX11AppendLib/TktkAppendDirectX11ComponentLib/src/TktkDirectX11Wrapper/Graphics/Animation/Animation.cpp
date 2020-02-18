#include "TktkDirectX11Wrapper/Graphics/Animation/Animation.h"

#include <stdexcept>
#include "TktkDirectX11Wrapper/Graphics/Animation/AnimationManager.h"

namespace tktk
{
	void Animation::create(int id, const std::unordered_map<std::string, std::vector<KeyFrame>>& boneKeyFrames)
	{
		if (id <= 0)
		{
			throw std::runtime_error("AnimationId Fraud Value");
		}
		AnimationManager::create(id, boneKeyFrames);
	}

	void Animation::erase(int id)
	{
		if (id <= 0)
		{
			throw std::runtime_error("AnimationId Fraud Value");
		}
		AnimationManager::erase(id);
	}

	const AnimationData & Animation::getData(int id)
	{
		return AnimationManager::getData(id);
	}
}