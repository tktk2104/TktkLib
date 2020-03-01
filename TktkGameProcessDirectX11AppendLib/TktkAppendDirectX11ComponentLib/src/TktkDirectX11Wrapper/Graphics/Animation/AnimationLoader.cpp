#include "TktkDirectX11Wrapper/Graphics/Animation/AnimationLoader.h"

#include <fstream>
#include "TktkDirectX11Wrapper/Graphics/Animation/Animation.h"

namespace tktk
{
	void AnimationLoader::loadImpl(int id, const std::string & fileName)
	{
		std::ifstream file(fileName, std::ios::binary);
		if (!file)
		{
			throw std::runtime_error("can not open" + fileName);
		}

		std::unordered_map<std::string, std::vector<KeyFrame>> boneKeyFrames;

		unsigned int boneFrameSize = 0;
		file.read(reinterpret_cast<char*>(&boneFrameSize), sizeof(boneFrameSize));

		for (unsigned int i = 0u; i < boneFrameSize; ++i)
		{
			char boneName[32];
			file.read(boneName, sizeof(boneName));
			unsigned int keyFrameSize = 0;
			file.read(reinterpret_cast<char*>(&keyFrameSize), sizeof(keyFrameSize));
			boneKeyFrames.insert(std::make_pair(boneName, std::vector<KeyFrame>(keyFrameSize)));
			file.read(reinterpret_cast<char*>(boneKeyFrames.at(boneName).data()), sizeof(KeyFrame) * keyFrameSize);
		}

		tktk::Animation::create(
			id,
			boneKeyFrames
		);
	}
}