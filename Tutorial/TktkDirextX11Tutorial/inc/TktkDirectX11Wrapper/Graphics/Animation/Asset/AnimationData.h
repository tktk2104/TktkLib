#ifndef ANIMATION_DATA_H_
#define ANIMATION_DATA_H_

#include <string>
#include <vector>
#include <unordered_map>
#include "KeyFrame.h"

namespace tktk
{
	// �A�j���[�V�������Ǘ�����N���X
	class AnimationData
	{
	public:

		explicit AnimationData(const std::unordered_map<std::string, std::vector<KeyFrame>>& boneKeyFrames);
		~AnimationData();

		AnimationData(const AnimationData& other) = delete;
		AnimationData& operator = (const AnimationData& other) = delete;

	public:

		// �w�肵���t���[���̃L�[�t���[�������v�Z����
		KeyFrame calculateKeyFrame(const std::string& boneName, float frameNo) const;

		// �A�j���[�V�����̏I���t���[����������
		float findEndFrameNo() const;

	private:

		// �{�[�����Ƃ̃L�[�t���[���̔z����Ǘ�����A�z�z��
		std::unordered_map<std::string, std::vector<KeyFrame>> m_boneKeyFrames;
	};
}
#endif // !ANIMATION_DATA_H_