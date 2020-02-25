#ifndef MESH_H_

#include "Assets/MeshData.h"

namespace tktk
{
	class Mesh
	{
	public:

		// �V���ȃ��b�V���f�[�^���쐬����
		// �����̊֐��Ń��b�V���f�[�^���쐬����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		static void create(
			int id,
			const VertexBufferInitParams& vertexBufferParams,
			const IndexBufferInitParams& indexBufferParams
		);

		// �w�肵�����b�V���f�[�^���폜����
		// �����̊֐��Ń��b�V���f�[�^���폜����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		static void erase(int id);

		// �w�肵�����b�V���f�[�^���Ǘ�����N���X�̃|�C���^���擾����
		static MeshData* getDataPtr(int id);
	};
}
#endif // !MESH_H_
