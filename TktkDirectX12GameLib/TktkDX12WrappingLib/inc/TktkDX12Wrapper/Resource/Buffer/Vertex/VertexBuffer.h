#ifndef VERTEX_BUFFER_H_
#define VERTEX_BUFFER_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "VertexBufferData.h"

namespace tktk
{
	// �uVertexBufferData�v���Ǘ�����N���X
	class VertexBuffer
	{
	public:

		VertexBuffer(unsigned int vertexBufferNum);
		~VertexBuffer() = default;

	public:

		// �uVertexBufferData�v�̃C���X�^���X�����
		void create(unsigned int id, ID3D12Device* device, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);

		// �R�}���h���X�g�Ɏw��̒��_�o�b�t�@��o�^����
		void set(unsigned int id, ID3D12GraphicsCommandList* commandList);

	private:

		HeapArray<VertexBufferData> m_vertexBufferDataArray;
	};
}
#endif // !VERTEX_BUFFER_H_