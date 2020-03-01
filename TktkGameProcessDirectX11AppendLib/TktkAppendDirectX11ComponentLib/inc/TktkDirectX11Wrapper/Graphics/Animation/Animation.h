#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include "Asset/AnimationData.h"

namespace tktk
{
	// �uAnimationManager�v�̎����̈ꕔ���B�����߂̃N���X
	class Animation
	{
	public:

		// �V���ȃA�j���[�V���������[�h����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		// �����̊֐��ŃA�j���[�V���������[�h����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const std::unordered_map<std::string, std::vector<KeyFrame>>& boneKeyFrames)
		{
			createImpl(static_cast<int>(id), boneKeyFrames);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const std::unordered_map<std::string, std::vector<KeyFrame>>& boneKeyFrames) { static_assert(false, "AnimationId Fraud Type"); }

		// �w�肵���A�j���[�V�������폜����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		// �����̊֐��ŃA�j���[�V�������폜����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "AnimationId Fraud Type"); }

		// �w�肵���A�j���[�V�������Ǘ�����N���X�̎Q�Ƃ��擾����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static const AnimationData& getData(IdType id)
		{
			return getDataImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static const AnimationData& getData(IdType id) { static_assert(false, "AnimationId Fraud Type"); }

	private:

		// �e��id�w��n�̊֐��̎���
		static void createImpl(int id, const std::unordered_map<std::string, std::vector<KeyFrame>>& boneKeyFrames);
		static void eraseImpl(int id);
		static const AnimationData& getDataImpl(int id);
	};
}
#endif // !ANIMATION_H_