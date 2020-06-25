#ifndef MOTION_BONE_PARAM_H_
#define MOTION_BONE_PARAM_H_

#include <string>
#include <TktkMath/Structs/Matrix4.h>

namespace tktk
{
	struct MotionBoneParam
	{
		std::string			boneName;
		tktkMath::Matrix4	transform;
	};
}
#endif // !MOTION_BONE_PARAM_H_
