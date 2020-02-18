#ifndef BONE_H_
#define BONE_H_

#include <string>
#include <TktkMath/Matrix4.h>

namespace tktk
{
	// ƒ{[ƒ“‚Ìî•ñ
	struct Bone
	{
		std::string	name;
		int			id;
		int			parentId;
		Matrix4		transform;
		Matrix4		inverse;
	};
}
#endif // !BONE_H_