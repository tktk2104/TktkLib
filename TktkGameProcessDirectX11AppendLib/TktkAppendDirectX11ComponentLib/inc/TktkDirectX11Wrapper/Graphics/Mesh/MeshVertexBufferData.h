#ifndef MESH_VERTEX_BUFFER_DATA_H_
#define MESH_VERTEX_BUFFER_DATA_H_

#include <TktkMath/Vector2.h>
#include <TktkMath/Vector3.h>

namespace tktk
{
	struct MeshVertexBufferData
	{
		Vector3 point;
		Vector3 normal;
		Vector2 texcoord;
		unsigned char bones[4];
		float weight[4];
		Vector3 tangent;
		Vector3 binormal;
	};
}
#endif // !MESH_VERTEX_BUFFER_DATA_H_
