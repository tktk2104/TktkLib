#ifndef SKELETON_H_
#define SKELETON_H_

#include "Asset/SkeletonData.h"

namespace tktk
{
	// �uSkeletonManager�v�̎����̈ꕔ���B�����߂̃N���X
	class Skeleton
	{
	public:

		// �V�����X�P���g�����쐬����
		// �����̊֐��ŃX�P���g�������ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		static void create(int id, const std::vector<Bone>& boneArray);

		// �w�肵���X�P���g�����폜����
		// �����̊֐��ŃX�P���g�����폜����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		static void erase(int id);

		// �w�肵���X�P���g�����Ǘ�����N���X�̎Q�Ƃ��擾����
		static const SkeletonData& getData(int id);
	};
}
#endif // !SKELETON_H_