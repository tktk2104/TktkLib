#ifndef BASIC_MESH_MATERIAL_H_
#define BASIC_MESH_MATERIAL_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include <TktkDX12Wrapper/Resource/GraphicsPipeLine/PipeLineState/PipeLineStateInitParam.h>
#include "BasicMeshMaterialData.h"

namespace tktk
{
	// �uBasicMeshMaterialData�v���Ǘ�����N���X
	class BasicMeshMaterial
	{
	public:

		BasicMeshMaterial(const ShaderFilePaths& shaderFilePaths, unsigned int basicMeshMaterialNum);
		~BasicMeshMaterial() = default;

	public:

		// �uBasicMeshMaterialData�v�̃C���X�^���X�����
		void create(unsigned int id, const BasicMeshMaterialInitParam& initParam);

		// �w��̒ʏ탁�b�V���̃}�e���A�������O���t�B�b�N�p�C�v���C���ɐݒ肷��
		void setMaterialData(unsigned int id)  const;

	private:

		// �ʏ탁�b�V���}�e���A���`��p�̃��[�g�V�O�l�`�������
		void createRootSignature() const;

		// �ʏ탁�b�V���}�e���A���`��p�̃p�C�v���C���X�e�[�g�����
		void createGraphicsPipeLineState(const ShaderFilePaths& shaderFilePaths) const;

	private:

		HeapArray<BasicMeshMaterialData> m_basicMeshMaterialArray;
	};
}
#endif // !BASIC_MESH_MATERIAL_H_