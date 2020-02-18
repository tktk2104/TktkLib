#ifndef KEY_FRAME_H_
#define KEY_FRAME_H_

#include <TktkMath/Vector3.h>
#include <TktkMath/Quaternion.h>

namespace tktk
{
	struct KeyFrame
	{
		float		frameNo;
		Vector3		scale;
		Quaternion	rotate;
		Vector3		position;
	};
}
#endif // !KEY_FRAME_H_