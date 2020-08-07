#ifndef BASIC_MESH_H_
#define BASIC_MESH_H_

#include <string>
#include <TktkContainer/HeapArray/HeapArray.h>
#include "BasicMeshData.h"

namespace tktk
{
	// �uBasicMeshData�v���Ǘ�����N���X
	class BasicMesh
	{
	public:

		BasicMesh(const std::string& writeShadowMapVsFilePath, unsigned int basicMeshNum);
	
	public:

		// �uBasicMeshData�v�̃C���X�^���X�����
		void craete(unsigned int id, const BasicMeshInitParam& initParam);

		// �w��́uBasicMeshData�v�̃C���X�^���X�̃R�s�[�����
		void copy(unsigned int id, unsigned int originalId);

		// �g�p���Ă���}�e���A�����X�V����
		void setMaterialId(unsigned int id, unsigned int materialSlot, unsigned int materialId);

		// �w��̒ʏ탁�b�V���ŃV���h�E�}�b�v����������
		void writeShadowMap(unsigned int id, const MeshTransformCbuffer& transformBufferData) const;

		// �w��̒ʏ탁�b�V����`�悷��
		void drawMesh(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs) const;

	private:

		// �V���h�E�}�b�v�������ݗp�̃��[�g�V�O�l�`�������
		void createWriteShadowMapRootSignature() const;

		// �V���h�E�}�b�v�������ݗp�̃p�C�v���C���X�e�[�g�����
		void createWriteShadowMapGraphicsPipeLineState(const std::string& writeShadowMapVsFilePath) const;

		// ���b�V���̍��W�ϊ��p�̒萔�o�b�t�@���X�V����
		void updateMeshTransformCbuffer(const MeshTransformCbuffer& transformBufferData) const;

		// ���b�V���̃V���h�E�}�b�v�g�p�p�̒萔�o�b�t�@���X�V����
		void updateMeshShadowMapCBuffer(const MeshShadowMapCBuffer&	shadowMapBufferData) const;

	private:

		HeapArray<BasicMeshData> m_basicMeshArray;
	};
}
#endif // !BASIC_MESH_H_