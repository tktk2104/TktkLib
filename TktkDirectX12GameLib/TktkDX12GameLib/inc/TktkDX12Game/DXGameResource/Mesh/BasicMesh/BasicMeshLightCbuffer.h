#ifndef BASIC_MESH_LIGHT_CBUFFER_H_
#define BASIC_MESH_LIGHT_CBUFFER_H_

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Matrix4.h>

namespace tktk
{
	// 通常メッシュのライティングの定数バッファ
	struct BasicMeshLightCbuffer
	{
		// ライトの環境光
		tktkMath::Color		lightAmbient	{ 0.25f, 1.0f };

		// ライトの拡散反射光
		tktkMath::Color		lightDiffuse	{ 0.25f, 1.0f };

		// ライトの鏡面反射光
		tktkMath::Color		lightSpeqular	{ 0.25f, 1.0f };

		// ライトの座標
		tktkMath::Vector3	lightPosition	{ tktkMath::vec3Zero };

		// パディング
		float				lightDataPad	{ 0.0f };

		// ライト行列
		tktkMath::Matrix4	lightMatrix		{ tktkMath::mat4Identity };
	};
}
#endif // !BASIC_MESH_LIGHT_CBUFFER_H_
