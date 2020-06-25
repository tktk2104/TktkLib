#ifndef SKELETON_INIT_PARAM_H_
#define SKELETON_INIT_PARAM_H_

#include <string>
#include <vector>
#include <TktkMath/Structs/Vector3.h>

namespace tktk
{
	struct SkeletonInitParam
	{
		struct BoneData
		{
			std::string			boneName;
			unsigned short		parentNo;
			tktkMath::Vector3	pos;
		};

		std::vector<BoneData> boneDataArray;
	};
}
#endif // !SKELETON_INIT_PARAM_H_
