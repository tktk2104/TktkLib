#ifndef BASIC_MESH_MATERIAL_INIT_PARAM_H_
#define BASIC_MESH_MATERIAL_INIT_PARAM_H_

#include <TktkMath/Structs/Color.h>

namespace tktk
{
	// �ʏ탁�b�V���̃}�e���A�������Ƃ��K�v�ȏ��
	struct BasicMeshMaterialInitParam
	{
		// ���f�B�X�N���v�^�q�[�v��ID
		unsigned int						createDescriptorHeapId;

		// �g���A���x�h�}�b�v�̃e�N�X�`��ID
		unsigned int						useAlbedoMapTextureId;

		// �g���m�[�}���}�b�v�̃e�N�X�`��ID
		unsigned int						useNormalMapTextureId;

		// �}�e���A���̊���
		tktkMath::Color						materialAmbient		{ 0.25f, 1.0f };

		// �}�e���A���̊g�U���ˌ�
		tktkMath::Color						materialDiffuse		{ 0.25f, 1.0f };

		// �}�e���A���̋��ʔ��ˌ�
		tktkMath::Color						materialSpecular	{ 0.25f, 1.0f };

		// �}�e���A���̎��Ȕ���
		tktkMath::Color						materialEmissive	{ 0.25f, 1.0f };

		// �}�e���A���̋P�x
		float								materialShiniess	{ 1.0f };
	};
}
#endif // !BASIC_MESH_MATERIAL_INIT_PARAM_H_