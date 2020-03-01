#ifndef SKELETON_MANAGER_H_
#define SKELETON_MANAGER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/SkeletonAssets.h"

namespace tktk
{
	// �uSkeletonAssets�v�ɊȒP�ɃA�N�Z�X���邽�߂̃N���X
	class SkeletonManager
	{
	public:

		// �uSkeletonAssets�v�𐶐�
		static void setUp();

	public:

		// �V�����X�P���g�����쐬����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const std::vector<Bone>& boneArray)
		{
			createImpl(static_cast<int>(id), boneArray);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const std::vector<Bone>& boneArray) { static_assert(false, "SkeletonId Fraud Type"); }

		// �w�肵���X�P���g�����폜����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "SkeletonId Fraud Type"); }

		// �w�肵���X�P���g�����Ǘ�����N���X�̎Q�Ƃ��擾����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static const SkeletonData& getData(IdType id)
		{
			return getDataImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static const SkeletonData& getData(IdType id) { static_assert(false, "SkeletonId Fraud Type"); }

		// �S�ẴX�P���g�����폜����
		static void clear();

	private:

		// �e��id�w��n�̊֐��̎���
		static void createImpl(int id, const std::vector<Bone>& boneArray);
		static void eraseImpl(int id);
		static const SkeletonData& getDataImpl(int id);

	private:

		static CfpPtr<SkeletonAssets> m_assetsPtr;
	};
}
#endif // !SKELETON_MANAGER_H_