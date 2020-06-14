#ifndef MESH_WRITE_SHADOW_FUNC_BASE_ARGS_H_
#define MESH_WRITE_SHADOW_FUNC_BASE_ARGS_H_

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Matrix4.h>

namespace tktk
{
	struct MeshWriteShadowFuncBaseArgs
	{
		tktkMath::Matrix4					worldMatrix{ tktkMath::mat4Identity };
		tktkMath::Matrix4					viewMatrix{ tktkMath::mat4Identity };
		tktkMath::Matrix4					projectionMatrix{ tktkMath::mat4Identity };
		tktkMath::Matrix4					boneMatrix[128U]{ };
	};
}
#endif // !MESH_WRITE_SHADOW_FUNC_BASE_ARGS_H_