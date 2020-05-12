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
		unsigned int						useVertexBufferId	{ 0U };
		unsigned int						useIndexBufferId	{ 0U };

		unsigned int						indexBufferStartPos	{ 0U };
		unsigned int						indexBufferUseCount	{ 0U };
	};
}
#endif // !MESH_MATERIAL_DRAW_FUNC_ARGS_H_