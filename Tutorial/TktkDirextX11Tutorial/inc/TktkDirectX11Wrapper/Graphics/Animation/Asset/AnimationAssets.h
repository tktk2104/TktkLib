#ifndef ANIMATION_ASSETS_H_
#define ANIMATION_ASSETS_H_

#include <unordered_map>
#include "AnimationData.h"

namespace tktk
{
	// �uAnimationData�v���Ǘ�����N���X
	class AnimationAssets
	{
	public:

		AnimationAssets() = default;
		~AnimationAssets();

		AnimationAssets(const AnimationAssets& other) = delete;
		AnimationAssets& operator = (const AnimationAssets& other) = delete;

	public:

		// �V���ȃA�j���[�V�������쐬����
		void create(int id, const std::unordered_map<std::string, std::vector<KeyFrame>>& boneKeyFrames);

		// �w�肵���A�j���[�V�������폜����
		void erase(int id);

		// �S�ẴA�j���[�V�������폜����
		void clear();

		// �w�肵���A�j���[�V�������Ǘ�����N���X�̎Q�Ƃ��擾����
		const AnimationData& getData(int id) const;

	private:

		// �A�j���[�V�������Ǘ�����N���X�̘A�z�z��
		std::unordered_map<int, AnimationData> m_assets;
	};
}
#endif // !ANIMATION_ASSETS_H_