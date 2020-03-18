#ifndef MESH_DATA_H_
#define MESH_DATA_H_

#include "VertexBuffer/VertexBuffer.h"
#include "IndexBuffer/IndexBuffer.h"
#include "MaterialSlots/MaterialSlots.h"

#include "SystemMeshId.h"

namespace tktk
{
	class MeshData
	{
	public:

		MeshData(
			D3D_PRIMITIVE_TOPOLOGY primitiveTopology,
			const VertexBufferInitParams& vertexBufferParams,
			const IndexBufferInitParams& indexBufferParams,
			const MaterialSlotsInitParams& materialSlotsParams
		);
		~MeshData() = default;

		// �R�s�[�֎~
		MeshData(const MeshData& other) = delete;
		MeshData& operator = (const MeshData& other) = delete;

	public:

		// �ǂ��������_�̕��тŕ`�施�߂��s�����������_�����O�p�C�v���C���ɐݒ肷��
		void setPrimitiveTopology() const;

		// ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�������_�����O�p�C�v���C���ɐݒ肷��
		void setVertexAndIndexBuffer() const;

		// �}�e���A���X���b�g�������邩�擾����
		unsigned int getMaterialSlotCount() const;

		// �w�肵���}�e���A���X���b�g�̃T�u�Z�b�g���擾����
		const Subset& getSubset(unsigned int slotIndex) const;

	private:

		D3D_PRIMITIVE_TOPOLOGY m_primitiveTopology;
		VertexBuffer m_vertexBuffer;
		IndexBuffer m_indexBuffer;
		MaterialSlots m_materialSlots;
	};
}
#endif // !MESH_DATA_H_
