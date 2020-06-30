#ifndef MESH_DRAW_FUNC_BASE_ARGS_H_
#define MESH_DRAW_FUNC_BASE_ARGS_H_

#include <array>
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Matrix4.h>
#include "MeshTransformCbuffer.h"
#include "BasicMesh/BasicMeshLightCbuffer.h"

namespace tktk
{
	struct MeshDrawFuncBaseArgs
	{
		unsigned int			viewportId;
		unsigned int			scissorRectId;
		unsigned int			rtvDescriptorHeapId;
		unsigned int			dsvDescriptorHeapId;

		MeshTransformCbuffer	transformBufferData{};
		BasicMeshLightCbuffer	lightBufferData{};
	};
}
#endif // !MESH_DRAW_FUNC_BASE_ARGS_H_