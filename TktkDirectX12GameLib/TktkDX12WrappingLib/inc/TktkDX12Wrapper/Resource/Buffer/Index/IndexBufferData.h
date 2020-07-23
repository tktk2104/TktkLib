#ifndef INDEX_BUFFER_DATA_H_
#define INDEX_BUFFER_DATA_H_

#include <vector>
#include <d3d12.h>

namespace tktk
{
	// インデックスバッファを管理するクラス
	class IndexBufferData
	{
	public:

		IndexBufferData(ID3D12Device* device, const std::vector<unsigned short>& indexDataArray);
		~IndexBufferData();

	public:

		// コマンドリストにインデックスバッファを登録する
		void set(ID3D12GraphicsCommandList* commandList) const;

	private:

		ID3D12Resource*				m_indexBuffer{ nullptr };
		D3D12_INDEX_BUFFER_VIEW		m_indexBufferView{};
	};
}
#endif // !INDEX_BUFFER_DATA_H_
