#ifndef ANIMATION_MANAGER_H_
#define ANIMATION_MANAGER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
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

		// �V���ȃA�j���[�V���������[�h����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const std::unordered_map<std::string, std::vector<KeyFrame>>& boneKeyFrames)
		{
			createImpl(static_cast<int>(id), boneKeyFrames);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const std::unordered_map<std::string, std::vector<KeyFrame>>& boneKeyFrames) { static_assert(false, "AnimationId Fraud Type"); }

		// �w�肵���A�j���[�V�������폜����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
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

		// �S�ẴA�j���[�V�������폜����
		static void clear();

	private:

		// �e��id�w��n�̊֐��̎���
		static void createImpl(int id, const std::unordered_map<std::string, std::vector<KeyFrame>>& boneKeyFrames);
		static void eraseImpl(int id);
		static const AnimationData& getDataImpl(int id);

	private:

		static CfpPtr<AnimationAssets> m_assetsPtr;
	};
}
#endif // !ANIMATION_MANAGER_H_
