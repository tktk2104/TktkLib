#ifndef SKELETON_H_
#define SKELETON_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "SkeletonData.h"

namespace tktk
{
	class Skeleton
	{
	public:

		Skeleton(unsigned int skeletonNum);

	public:

		void create(unsigned int id, const SkeletonInitParam& initParam);

		void transform(unsigned int id, const std::vector<MotionBoneParam>& transformMatrices);

		void updateBoneMatrixCbuffer(unsigned int id);

	private:

		HeapArray<SkeletonData> m_skeletonArray;
	};
}
#endif // !SKELETON_H_