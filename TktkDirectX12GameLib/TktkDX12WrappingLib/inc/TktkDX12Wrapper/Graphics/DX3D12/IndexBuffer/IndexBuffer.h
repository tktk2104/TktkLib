#ifndef INDEX_BUFFER_H_
#define INDEX_BUFFER_H_

#include <vector>
#include "IndexBufferData.h"

namespace tktk
{
	class IndexBuffer
	{
	public:

		IndexBuffer(unsigned int indexBufferNum);

	public:

		void create(unsigned int id, ID3D12Device* device, const std::vector<unsigned short>& indexDataArray);

		void set(unsigned int id, ID3D12GraphicsCommandList* commandList);

	private:

		std::vector<IndexBufferData> m_indexBufferDataArray{};
	};
}
#endif // !INDEX_BUFFER_H_