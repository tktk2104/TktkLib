#ifndef BASIC_MESH_MATERIAL_APPEND_PARAM_H_
#define BASIC_MESH_MATERIAL_APPEND_PARAM_H_

#include <memory>
#include <utility>

namespace tktk
{
	class BasicMeshMaterialAppendParam
	{
	public:

		BasicMeshMaterialAppendParam(unsigned int cbufferId, unsigned int dataSize, void* dataTopPos);

	public:

		// �萔�o�b�t�@���X�V������e�̕ϐ�������������
		void updateParam(unsigned int dataSize, const void* dataTopPos);

		// �萔�o�b�t�@���X�V����
		void updateCbuffer() const;


	private:

		// �ύX�Ώۂ̒萔�o�b�t�@ID
		unsigned int m_cbufferId;

		// �萔�o�b�t�@�̑傫��
		unsigned int m_dataSize;

		// �萔�o�b�t�@���X�V������e�̕ϐ��̃|�C���^
		std::shared_ptr<void> m_dataTopPos;
	};
}
#endif // !BASIC_MESH_MATERIAL_APPEND_PARAM_H_