#ifndef MESH_CONSTANT_BUFFER_DATA_H_
#define MESH_CONSTANT_BUFFER_DATA_H_

#include <TktkMath/Color.h>
#include <TktkMath/Vector3.h>
#include <TktkMath/Matrix4.h>

namespace tktk
{
	// デフォルトのメッシュ描画の定数バッファの形式
	struct MeshConstantBufferData
	{
		Matrix4 world;
		Matrix4 view;
		Matrix4 projection;
		Matrix4 boneMatrices[256];

		Color matAmbient;
		Color matDiffuse;
		Color matSpecular;
		Color matEmissive;
		float matShiniess;
		float pad0[3];

		Color lightAmbient;
		Color lightDiffuse;
		Color lightSpecular;
		Vector3 lightPosition;
		float pad1[1];
	};
}
#endif // !MESH_CONSTANT_BUFFER_DATA_H_
