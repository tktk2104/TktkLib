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

		template <class VertexData>
		void create(unsigned int id, ID3D12Device* device, const std::vector<VertexData>& vertexDataArray);

		void set(unsigned int id, ID3D12GraphicsCommandList* commandList);

	private:

		HeapArray<VertexBufferData> m_vertexBufferDataArray;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	template<class VertexData>
	inline void VertexBuffer::create(unsigned int id, ID3D12Device* device, const std::vector<VertexData>& vertexDataArray)
	{
		m_vertexBufferDataArray.emplaceAt(id, device, vertexDataArray);
	}
}
#endif // !VERTEX_BUFFER_H_