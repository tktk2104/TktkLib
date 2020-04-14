#ifndef VERTEX_BUFFER_H_
#define VERTEX_BUFFER_H_

#include <array>
#include "VertexBufferData.h"

namespace tktk
{
	template <int VertexBufferNum>
	class VertexBuffer
	{
	public:

		VertexBuffer() = default;

	public:

		template <int VertexBufferIndex, class VertexData>
		void create(ID3D12Device* device, const std::vector<VertexData>& vertexDataArray);

		template <int VertexBufferIndex>
		void set(ID3D12GraphicsCommandList* commandList);

	private:

		std::array<VertexBufferData, VertexBufferNum> m_vertexBufferDataArray{};
	};

	template<int VertexBufferNum>
	template<int VertexBufferIndex, class VertexData>
	inline void VertexBuffer<VertexBufferNum>::create(ID3D12Device* device, const std::vector<VertexData>& vertexDataArray)
	{
		m_vertexBufferDataArray.at(VertexBufferIndex).initialize(device, vertexDataArray);
	}

	template<int VertexBufferNum>
	template<int VertexBufferIndex>
	inline void VertexBuffer<VertexBufferNum>::set(ID3D12GraphicsCommandList* commandList)
	{
		m_vertexBufferDataArray.at(VertexBufferIndex).set(commandList);
	}
}
#endif // !VERTEX_BUFFER_H_