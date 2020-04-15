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

		template <class VertexData>
		void create(unsigned int id, ID3D12Device* device, const std::vector<VertexData>& vertexDataArray);

		void set(unsigned int id, ID3D12GraphicsCommandList* commandList);

	private:

		std::array<VertexBufferData, VertexBufferNum> m_vertexBufferDataArray{};
	};

	template<int VertexBufferNum>
	template<class VertexData>
	inline void VertexBuffer<VertexBufferNum>::create(unsigned int id, ID3D12Device* device, const std::vector<VertexData>& vertexDataArray)
	{
		m_vertexBufferDataArray.at(id).initialize(device, vertexDataArray);
	}

	template<int VertexBufferNum>
	inline void VertexBuffer<VertexBufferNum>::set(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		m_vertexBufferDataArray.at(id).set(commandList);
	}
}
#endif // !VERTEX_BUFFER_H_