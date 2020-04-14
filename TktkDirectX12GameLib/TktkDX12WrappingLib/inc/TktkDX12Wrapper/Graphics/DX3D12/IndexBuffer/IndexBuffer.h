#ifndef INDEX_BUFFER_H_
#define INDEX_BUFFER_H_

#include <array>
#include "IndexBufferData.h"

namespace tktk
{
	template <int IndexBufferNum>
	class IndexBuffer
	{
	public:

		IndexBuffer() = default;

	public:

		template <int IndexBufferIndex>
		void create(ID3D12Device* device, const std::vector<unsigned short>& indexDataArray);

		template <int IndexBufferIndex>
		void set(ID3D12GraphicsCommandList* commandList);

	private:

		std::array<IndexBufferData, IndexBufferNum> m_indexBufferDataArray{};
	};

	template<int IndexBufferNum>
	template<int IndexBufferIndex>
	inline void IndexBuffer<IndexBufferNum>::create(ID3D12Device* device, const std::vector<unsigned short>& indexDataArray)
	{
		m_indexBufferDataArray.at(IndexBufferIndex).initialize(device, indexDataArray);
	}

	template<int IndexBufferNum>
	template<int IndexBufferIndex>
	inline void IndexBuffer<IndexBufferNum>::set(ID3D12GraphicsCommandList* commandList)
	{
		m_indexBufferDataArray.at(IndexBufferIndex).set(commandList);
	}
}
#endif // !INDEX_BUFFER_H_