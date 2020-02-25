#ifndef SKELETON_DATA_H_
#define SKELETON_DATA_H_

#include <string>
#include <vector>
#include "Bone.h"

namespace tktk
{
	// �X�P���g�����Ǘ�����N���X
	class SkeletonData
	{
	public:

		explicit SkeletonData(const std::vector<Bone>& boneArray);
		~SkeletonData();

		SkeletonData(const SkeletonData& other) = delete;
		SkeletonData& operator = (const SkeletonData& other) = delete;

	public:

		// �{�[���̐����擾����
		unsigned int getSize() const;

		// �{�[�����̔z����擾����
		const std::vector<Bone>& getBoneArray() const;

	private:

		std::vector<Bone> m_boneArray;
	};
}
#endif // !SKELETON_DATA_H_