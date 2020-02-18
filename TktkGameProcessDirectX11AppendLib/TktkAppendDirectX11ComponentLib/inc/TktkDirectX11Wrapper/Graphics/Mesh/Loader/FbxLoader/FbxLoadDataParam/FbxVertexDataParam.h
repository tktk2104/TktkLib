#ifndef FBX_VERTEX_DATA_PARAM_H_
#define FBX_VERTEX_DATA_PARAM_H_

#include <TktkMath/Vector2.h>
#include <TktkMath/Vector3.h>

namespace tktk
{
	struct FbxVertexDataParam
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
#endif // !FBX_VERTEX_DATA_PARAM_H_