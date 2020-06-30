#ifndef BASIC_MESH_LIGHT_CBUFFER_H_
#define BASIC_MESH_LIGHT_CBUFFER_H_

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Matrix4.h>

namespace tktk
{
	struct BasicMeshLightCbuffer
	{
		tktkMath::Color		lightAmbient{ tktkMath::colorBlack };
		tktkMath::Color		lightDiffuse{ tktkMath::colorWhite };
		tktkMath::Color		lightSpeqular{ tktkMath::colorWhite };
		tktkMath::Vector3	lightPosition{ tktkMath::vec3Zero };
		float				lightDataPad{ 0.0f };
		tktkMath::Matrix4	lightMatrix{ tktkMath::mat4Identity };
	};
}
#endif // !BASIC_MESH_LIGHT_CBUFFER_H_
