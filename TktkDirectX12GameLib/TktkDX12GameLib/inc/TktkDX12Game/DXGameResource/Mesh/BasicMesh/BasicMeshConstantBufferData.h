#ifndef BASIC_MESH_CONSTANT_BUFFER_DATA_H_
#define BASIC_MESH_CONSTANT_BUFFER_DATA_H_

#include <array>
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Matrix4.h>

namespace tktk
{
	struct BasicMeshConstantBufferData
	{
		tktkMath::Matrix4					worldMatrix			{ tktkMath::mat4Identity };
		tktkMath::Matrix4					viewMatrix			{ tktkMath::mat4Identity };
		tktkMath::Matrix4					projectionMatrix	{ tktkMath::mat4Identity };
		//tktkMath::Matrix4					boneMatrix[128U]	{ };

		tktkMath::Color						lightAmbient		{ tktkMath::colorBlack };
		tktkMath::Color						lightDiffuse		{ tktkMath::colorWhite };
		tktkMath::Color						lightSpeqular		{ tktkMath::colorWhite };
		tktkMath::Vector3					lightPosition		{ tktkMath::vec3Zero };
		float								lightDataPad		{ 0.0f };
		tktkMath::Matrix4					lightMatrix			{ tktkMath::mat4Identity };

		tktkMath::Color						materialAmbient		{ tktkMath::colorBlack };
		tktkMath::Color						materialDiffuse		{ tktkMath::colorWhite };
		tktkMath::Color						materialSpecular	{ tktkMath::colorWhite };
		tktkMath::Color						materialEmissive	{ tktkMath::colorWhite };
		float								materialShiniess	{ 1.0f };
		float								materialDataPad[3]	{ 0.0f, 0.0f, 0.0f };
	};


	struct BasicMeshBoneMatrix
	{
		tktkMath::Matrix4					boneMatrix[128U]	{ };
	};
}
#endif // !BASIC_MESH_CONSTANT_BUFFER_DATA_H_