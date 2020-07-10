#ifndef BASIC_MESH_MATERIAL_H_
#define BASIC_MESH_MATERIAL_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include <TktkDX12Wrapper/Graphics/DX3D12/DX3DResource/GraphicsPipeLine/PipeLineState/PipeLineStateInitParam.h>
#undef min
#undef max
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
		void setMaterialData(unsigned int id);

	private:

		// �ʏ탁�b�V���}�e���A���`��p�̃��[�g�V�O�l�`�������
		void createRootSignature();

		// �ʏ탁�b�V���}�e���A���`��p�̃p�C�v���C���X�e�[�g�����
		void createGraphicsPipeLineState(const ShaderFilePaths& shaderFilePaths);

	private:

		HeapArray<BasicMeshMaterialData> m_basicMeshMaterialArray;
	};
}
#endif // !BASIC_MESH_MATERIAL_H_