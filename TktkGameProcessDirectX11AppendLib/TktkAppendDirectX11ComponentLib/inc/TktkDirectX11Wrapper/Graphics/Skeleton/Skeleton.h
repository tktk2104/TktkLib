#ifndef SKELETON_H_
#define SKELETON_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include "Asset/SkeletonData.h"

namespace tktk
{
	// �uSkeletonManager�v�̎����̈ꕔ���B�����߂̃N���X
	class Skeleton
	{
	public:

		// �V�����X�P���g�����쐬����
		// �����̊֐��ŃX�P���g�������ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const std::vector<Bone>& boneArray)
		{
			createImpl(static_cast<int>(id), boneArray);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const std::vector<Bone>& boneArray) { static_assert(false, "SkeletonId Fraud Type"); }

		// �w�肵���X�P���g�����폜����
		// �����̊֐��ŃX�P���g�����폜����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "SkeletonId Fraud Type"); }

		// �w�肵���X�P���g�����Ǘ�����N���X�̎Q�Ƃ��擾����
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static const SkeletonData& getData(IdType id)
		{
			return getDataImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static const SkeletonData& getData(IdType id) { static_assert(false, "SkeletonId Fraud Type"); }

	private:

		// �e��id�w��n�̊֐��̎���
		static void createImpl(int id, const std::vector<Bone>& boneArray);
		static void eraseImpl(int id);
		static const SkeletonData& getDataImpl(int id);
	};
}
#endif // !SKELETON_H_