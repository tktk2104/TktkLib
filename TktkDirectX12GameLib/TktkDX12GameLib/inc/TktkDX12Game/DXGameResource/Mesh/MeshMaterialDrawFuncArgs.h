#ifndef MESH_MATERIAL_DRAW_FUNC_ARGS_H_
#define MESH_MATERIAL_DRAW_FUNC_ARGS_H_

#include <array>
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Matrix4.h>

namespace tktk
{
	struct MeshMaterialDrawFuncArgs
	{
		unsigned int useVertexBufferId;
		unsigned int useIndexBufferId;

		unsigned int indexBufferStartPos;
		unsigned int indexBufferUseCount;
	};
}
#endif // !MESH_MATERIAL_DRAW_FUNC_ARGS_H_