#ifndef MESH_TRANSFORM_CBUFFER_H_
#define MESH_TRANSFORM_CBUFFER_H_

#include <TktkMath/Structs/Matrix4.h>

namespace tktk
{
	struct MeshTransformCbuffer
	{
		tktkMath::Matrix4	worldMatrix		{ tktkMath::mat4Identity };
		tktkMath::Matrix4	viewMatrix		{ tktkMath::mat4Identity };
		tktkMath::Matrix4	projectionMatrix{ tktkMath::mat4Identity };
	};
}
#endif // !MESH_TRANSFORM_CBUFFER_H_