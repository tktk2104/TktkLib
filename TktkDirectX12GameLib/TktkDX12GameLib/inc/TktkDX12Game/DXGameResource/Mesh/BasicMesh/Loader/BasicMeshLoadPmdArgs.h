#ifndef BASIC_MESH_LOAD_PMD_ARGS_H_
#define BASIC_MESH_LOAD_PMD_ARGS_H_

#include <string>

namespace tktk
{
	// pmd�t�@�C����ǂݍ��ނƂ��ɕK�v�ȏ��
	struct BasicMeshLoadPmdArgs
	{
		// �쐬����ʏ탁�b�V���}�e���A���̃f�B�X�N���v�^�q�[�v�̊J�nID�i�����}�e���A��������ꍇ�A���̒l����Ƃ����A��ID�ƂȂ�j
		unsigned int createDescriptorHeapIdStartNum;

		// �쐬���钸�_�o�b�t�@��ID
		unsigned int createVertexBufferId;

		// �쐬����C���f�b�N�X�o�b�t�@��ID
		unsigned int createIndexBufferId;
		
		// �쐬����ʏ탁�b�V������ID
		unsigned int createBasicMeshId;

		// �쐬����X�P���g������ID
		unsigned int createSkeletonId;

		// �쐬����ʏ탁�b�V���}�e���A���̊J�nID�i�����}�e���A��������ꍇ�A���̒l����Ƃ����A��ID�ƂȂ�j
		unsigned int createBasicMeshMaterialIdStartNum;

		// �쐬����e�N�X�`���̊J�nID�i�����e�N�X�`��������ꍇ�A���̒l����Ƃ����A��ID�ƂȂ�j
		unsigned int createTextureIdStartNum;

		// �ǂݍ��ރt�@�C���p�X
		std::string filePath;
	};
}
#endif // !BASIC_MESH_LOAD_PMD_ARGS_H_
