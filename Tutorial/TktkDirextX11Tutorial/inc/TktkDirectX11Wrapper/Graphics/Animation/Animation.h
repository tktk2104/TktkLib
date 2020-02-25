#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "Asset/AnimationData.h"

namespace tktk
{
	// �uAnimationManager�v�̎����̈ꕔ���B�����߂̃N���X
	class Animation
	{
	public:

		// �V���ȃA�j���[�V���������[�h����
		// �����̊֐��ŃA�j���[�V���������[�h����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		static void create(int id, const std::unordered_map<std::string, std::vector<KeyFrame>>& boneKeyFrames);

		// �w�肵���A�j���[�V�������폜����
		// �����̊֐��ŃA�j���[�V�������폜����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		static void erase(int id);

		// �w�肵���A�j���[�V�������Ǘ�����N���X�̎Q�Ƃ��擾����
		static const AnimationData& getData(int id);
	};
}
#endif // !ANIMATION_H_