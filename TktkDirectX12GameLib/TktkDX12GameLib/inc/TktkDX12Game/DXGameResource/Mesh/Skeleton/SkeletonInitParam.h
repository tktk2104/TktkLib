#ifndef SKELETON_INIT_PARAM_H_
#define SKELETON_INIT_PARAM_H_

#include <string>
#include <vector>
#include <TktkMath/Structs/Vector3.h>

namespace tktk
{
	// �X�P���g�������Ƃ��ɕK�v�ȏ��
	struct SkeletonInitParam
	{
		// �{�[�����̏��
		struct BoneData
		{
			// �{�[���̖��O
			std::string			boneName;

			// �e��ID
			unsigned short		parentNo;

			// �{�[���̈ʒu
			tktkMath::Vector3	pos;
		};

		// �{�[�����̔z��
		std::vector<BoneData> boneDataArray;
	};
}
#endif // !SKELETON_INIT_PARAM_H_
