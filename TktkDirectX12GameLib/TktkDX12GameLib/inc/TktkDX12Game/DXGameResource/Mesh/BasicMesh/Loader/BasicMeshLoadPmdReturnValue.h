#ifndef BASIC_MESH_LOAD_PMD_RETURN_VALUE_H_
#define BASIC_MESH_LOAD_PMD_RETURN_VALUE_H_

namespace tktk
{
	// pmd�t�@�C����ǂݍ��񂾌��ʂ̒l
	struct BasicMeshLoadPmdReturnValue
	{
		// ��ԍŌ�ɍ쐬�����ʏ탁�b�V���̃f�B�X�N���v�^�q�[�v��ID
		unsigned int createDescriptorHeapIdEndNum;

		// ��ԍŌ�ɍ쐬�����ʏ탁�b�V���}�e���A����ID
		unsigned int createBasicMeshMaterialIdEndNum;

		// ��ԍŌ�ɍ쐬�����e�N�X�`����ID
		unsigned int createTextureIdEndNum;
	};
}
#endif // !BASIC_MESH_LOAD_PMD_RETURN_VALUE_H_
