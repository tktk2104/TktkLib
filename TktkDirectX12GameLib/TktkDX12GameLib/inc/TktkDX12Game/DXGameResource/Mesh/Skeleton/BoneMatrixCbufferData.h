#ifndef BONE_MATRIX_CBUFFER_DATA_H_
#define BONE_MATRIX_CBUFFER_DATA_H_

#include <TktkMath/Structs/Matrix4.h>

namespace tktk
{
	struct BoneMatrixCbufferData
	{
		tktkMath::Matrix4 boneMatrix[128U]{ };
	};
}
#endif // !BONE_MATRIX_CBUFFER_DATA_H_