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
		tktkMath::Matrix4					worldMatrix		{ tktkMath::mat4Identity };
		tktkMath::Matrix4					viewMatrix		{ tktkMath::mat4Identity };
		tktkMath::Matrix4					projectionMatrix{ tktkMath::mat4Identity };
		//tktkMath::Matrix4					boneMatrix[256U]{ };

		tktkMath::Color						lightAmbient	{ tktkMath::colorBlack };
		tktkMath::Color						lightDiffuse	{ tktkMath::colorWhite };
		tktkMath::Color						lightSpeqular	{ tktkMath::colorWhite };
		tktkMath::Vector3					lightPosition	{ tktkMath::vec3Zero };

	};
}
#endif // !MESH_DRAW_FUNC_BASE_ARGS_H_