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

		void create(unsigned int id, ID3D12Device* device, const std::vector<unsigned short>& indexDataArray);

		void set(unsigned int id, ID3D12GraphicsCommandList* commandList);

	private:

		std::array<IndexBufferData, IndexBufferNum> m_indexBufferDataArray{};
	};

	template<int IndexBufferNum>
	inline void IndexBuffer<IndexBufferNum>::create(unsigned int id, ID3D12Device* device, const std::vector<unsigned short>& indexDataArray)
	{
		m_indexBufferDataArray.at(id).initialize(device, indexDataArray);
	}

	template<int IndexBufferNum>
	inline void IndexBuffer<IndexBufferNum>::set(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		m_indexBufferDataArray.at(id).set(commandList);
	}
}
#endif // !INDEX_BUFFER_H_