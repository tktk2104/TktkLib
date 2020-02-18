#ifndef MESH_MANAGER_H_
#define MESH_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Assets/MeshAssets.h"

namespace tktk
{
	class MeshManager
	{
	public:
		
		static void setUp();

	public:

		// �V���ȃ��b�V���f�[�^���쐬����
		static void create(
			int id,
			const VertexBufferInitParams& vertexBufferParams,
			const IndexBufferInitParams& indexBufferParams
		);

		// �w�肵�����b�V���f�[�^���폜����
		static void erase(int id);

		// �S�Ẵ��b�V���f�[�^���폜����
		static void clear();

		// �w�肵�����b�V���f�[�^���Ǘ�����N���X�̃|�C���^���擾����
		static MeshData* getDataPtr(int id);

	private:

		static CfpPtr<MeshAssets> m_assetsPtr;
	};
}
#endif // !MESH_MANAGER_H_
