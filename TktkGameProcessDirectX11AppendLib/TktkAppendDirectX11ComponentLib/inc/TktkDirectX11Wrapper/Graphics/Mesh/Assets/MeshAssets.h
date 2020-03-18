#ifndef MESH_ASSETS_H_
#define MESH_ASSETS_H_

#include <unordered_map>
#include "MeshData.h"

namespace tktk
{
	class MeshAssets
	{
	public:
		MeshAssets() = default;
		~MeshAssets();

		MeshAssets(const MeshAssets& other) = delete;
		MeshAssets& operator = (const MeshAssets& other) = delete;

	public:

		// �V���ȃ��b�V���f�[�^���쐬����
		void create(
			int id,
			D3D_PRIMITIVE_TOPOLOGY primitiveTopology,
			const VertexBufferInitParams& vertexBufferParams,
			const IndexBufferInitParams& indexBufferParams,
			const MaterialSlotsInitParams& materialSlotsParams
		);

		// �w�肵�����b�V���f�[�^���폜����
		void erase(int id);

		// �S�Ẵ��b�V���f�[�^���폜����
		void clear();

		// �w�肵�����b�V���f�[�^���Ǘ�����N���X�̃|�C���^���擾����
		MeshData* getDataPtr(int id);

	private:

		std::unordered_map<int, MeshData> m_assets;
	};
}
#endif // !MESH_ASSETS_H_
