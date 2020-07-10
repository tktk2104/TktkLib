#ifndef BASIC_MESH_MATERIAL_CBUFFER_H_
#define BASIC_MESH_MATERIAL_CBUFFER_H_

#include <TktkMath/Structs/Color.h>

namespace tktk
{
	// �ʏ탁�b�V���̃}�e���A���̒萔�o�b�t�@
	struct BasicMeshMaterialCbuffer
	{
		// �}�e���A���̊���
		tktkMath::Color	materialAmbient		{ 0.25f, 1.0f };

		// �}�e���A���̊g�U���ˌ�
		tktkMath::Color	materialDiffuse		{ 0.25f, 1.0f };

		// �}�e���A���̋��ʔ��ˌ�
		tktkMath::Color	materialSpecular	{ 0.25f, 1.0f };

		// �}�e���A���̎��Ȕ���
		tktkMath::Color	materialEmissive	{ 0.25f, 1.0f };

		// �}�e���A���̋P�x
		float			materialShiniess	{ 1.0f };

		// �p�f�B���O
		float			materialDataPad[3]	{ 0.0f, 0.0f, 0.0f };
	};
}
#endif // !BASIC_MESH_MATERIAL_CBUFFER_H_
