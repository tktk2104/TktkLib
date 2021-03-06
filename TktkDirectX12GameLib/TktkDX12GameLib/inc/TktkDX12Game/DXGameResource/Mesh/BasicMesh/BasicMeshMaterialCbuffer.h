#ifndef BASIC_MESH_MATERIAL_CBUFFER_H_
#define BASIC_MESH_MATERIAL_CBUFFER_H_

#include <TktkMath/Structs/Color.h>

namespace tktk
{
	// 通常メッシュのマテリアルの定数バッファ
	struct BasicMeshMaterialCbuffer
	{
		// マテリアルの環境光
		tktkMath::Color	materialAmbient		{ 0.25f, 1.0f };

		// マテリアルの拡散反射光
		tktkMath::Color	materialDiffuse		{ 0.25f, 1.0f };

		// マテリアルの鏡面反射光
		tktkMath::Color	materialSpecular	{ 0.25f, 1.0f };

		// マテリアルの自己発光
		tktkMath::Color	materialEmissive	{ 0.25f, 1.0f };

		// マテリアルの輝度
		float			materialShiniess	{ 1.0f };

		// パディング
		float			materialDataPad[3]	{ 0.0f, 0.0f, 0.0f };
	};
}
#endif // !BASIC_MESH_MATERIAL_CBUFFER_H_
