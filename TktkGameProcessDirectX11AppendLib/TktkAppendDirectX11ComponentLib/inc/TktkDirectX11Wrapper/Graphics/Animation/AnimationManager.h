#ifndef ANIMATION_MANAGER_H_
#define ANIMATION_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/AnimationAssets.h"

namespace tktk
{
	// �uAnimationAssets�v�ɊȒP�ɃA�N�Z�X���邽�߂̃N���X
	class AnimationManager
	{
	public:

		// �uAnimationAssets�v�𐶐�
		static void setUp();

	public:

		// �V���ȃA�j���[�V���������[�h����
		static void create(int id, const std::unordered_map<std::string, std::vector<KeyFrame>>& boneKeyFrames);

		// �w�肵���A�j���[�V�������폜����
		static void erase(int id);

		// �S�ẴA�j���[�V�������폜����
		static void clear();

		// �w�肵���A�j���[�V�������Ǘ�����N���X�̎Q�Ƃ��擾����
		static const AnimationData& getData(int id);

	private:

		static CfpPtr<AnimationAssets> m_assetsPtr;
	};
}
#endif // !ANIMATION_MANAGER_H_
