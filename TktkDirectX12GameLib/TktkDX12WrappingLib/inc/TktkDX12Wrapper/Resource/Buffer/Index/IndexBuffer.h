#ifndef INDEX_BUFFER_H_
#define INDEX_BUFFER_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "IndexBufferData.h"

namespace tktk
{
	// 「IndexBufferData」を管理するクラス
	class IndexBuffer
	{
	public:

		IndexBuffer(unsigned int indexBufferNum);
		~IndexBuffer() = default;

	public:

		// 「IndexBufferData」のインスタンスを作る
		void create(unsigned int id, ID3D12Device* device, const std::vector<unsigned short>& indexDataArray);

		// コマンドリストに指定のインデックスバッファを登録する
		void set(unsigned int id, ID3D12GraphicsCommandList* commandList);

	private:

		HeapArray<IndexBufferData> m_indexBufferDataArray;
	};
}
#endif // !INDEX_BUFFER_H_