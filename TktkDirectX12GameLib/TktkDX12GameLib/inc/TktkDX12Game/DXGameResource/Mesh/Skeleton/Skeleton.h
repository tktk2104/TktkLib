#ifndef SKELETON_H_
#define SKELETON_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "SkeletonData.h"

namespace tktk
{
	// �uSkeletonData�v���Ǘ�����N���X
	class Skeleton
	{
	public:

		Skeleton(unsigned int skeletonNum);

	public:

		// �uSkeletonData�v�̃C���X�^���X�����
		void create(unsigned int id, const SkeletonInitParam& initParam);

		// �����̃{�[�����̍��W�ϊ��s����g���Ďw��̃X�P���g����ό`����
		void transform(unsigned int id, const std::vector<MotionBoneParam>& transformMatrices);

		// �w��̃X�P���g�����g���č������Ǘ�����萔�o�b�t�@���X�V����
		void updateBoneMatrixCbuffer(unsigned int id);

	private:

		HeapArray<SkeletonData> m_skeletonArray;
	};
}
#endif // !SKELETON_H_