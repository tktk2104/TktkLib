#ifndef INDEX_BUFFER_DATA_H_
#define INDEX_BUFFER_DATA_H_

#include <vector>
#include <d3d12.h>
#include <forward_list>

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

		// インデックスバッファを更新する
		// ※アップロードバッファを新規に作成し、そのバッファから自身にコピーする命令をコマンドリストに登録する
		void updateBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<unsigned short>& indexDataArray);

		// 全てのアップロード用のバッファを削除する
		void deleteUploadBufferAll();

	private:

		ID3D12Resource*				m_indexBuffer{ nullptr };
		D3D12_INDEX_BUFFER_VIEW		m_indexBufferView{};
		std::forward_list<ID3D12Resource*> m_uploadBufferList{};
	};
}
#endif // !INDEX_BUFFER_DATA_H_
