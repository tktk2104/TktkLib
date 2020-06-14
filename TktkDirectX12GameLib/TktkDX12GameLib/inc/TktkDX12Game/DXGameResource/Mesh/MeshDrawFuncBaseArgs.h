#ifndef MESH_DRAW_FUNC_BASE_ARGS_H_
#define MESH_DRAW_FUNC_BASE_ARGS_H_

#include <array>
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Matrix4.h>

namespace tktk
{
	struct MeshDrawFuncBaseArgs
	{
		unsigned int						viewportId;
		unsigned int						scissorRectId;
		unsigned int						rtvDescriptorHeapId;
		unsigned int						dsvDescriptorHeapId;

		tktkMath::Matrix4					worldMatrix		{ tktkMath::mat4Identity };
		tktkMath::Matrix4					viewMatrix		{ tktkMath::mat4Identity };
		tktkMath::Matrix4					projectionMatrix{ tktkMath::mat4Identity };
		tktkMath::Matrix4					boneMatrix[128U]{ };

		tktkMath::Color						lightAmbient	{ 0.3f, 1.0f };
		tktkMath::Color						lightDiffuse	{ tktkMath::colorWhite };
		tktkMath::Color						lightSpeqular	{ tktkMath::colorWhite };
		tktkMath::Vector3					lightPosition	{ tktkMath::vec3Zero };
		tktkMath::Matrix4					lightMatrix		{ tktkMath::mat4Identity };
	};
}
#endif // !MESH_DRAW_FUNC_BASE_ARGS_H_