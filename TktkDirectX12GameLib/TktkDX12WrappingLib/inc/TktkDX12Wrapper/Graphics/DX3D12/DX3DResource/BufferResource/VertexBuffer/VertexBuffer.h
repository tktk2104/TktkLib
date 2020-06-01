#ifndef VERTEX_BUFFER_H_
#define VERTEX_BUFFER_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "VertexBufferData.h"

namespace tktk
{
	class VertexBuffer
	{
	public:

		VertexBuffer(unsigned int vertexBufferNum);

	public:

		void create(unsigned int id, ID3D12Device* device, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);

		void set(unsigned int id, ID3D12GraphicsCommandList* commandList);

	private:

		HeapArray<VertexBufferData> m_vertexBufferDataArray;
	};
}
#endif // !VERTEX_BUFFER_H_