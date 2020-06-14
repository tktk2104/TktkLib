#ifndef BASIC_MESH_SHADOW_MAP_CBUFFER_DATA_H_
#define BASIC_MESH_SHADOW_MAP_CBUFFER_DATA_H_

#include <TktkMath/Structs/Matrix4.h>

namespace tktk
{
	struct BasicMeshShadowMapCbufferData
	{
		tktkMath::Matrix4					worldMatrix			{ tktkMath::mat4Identity };
		tktkMath::Matrix4					viewMatrix			{ tktkMath::mat4Identity };
		tktkMath::Matrix4					projectionMatrix	{ tktkMath::mat4Identity };
		tktkMath::Matrix4					boneMatrix[128U]	{ };
	};
}
#endif // !BASIC_MESH_SHADOW_MAP_CBUFFER_DATA_H_
