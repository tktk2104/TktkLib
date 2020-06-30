#ifndef CONSTANT_BUFFER_DATA_H_
#define CONSTANT_BUFFER_DATA_H_

#include <d3d12.h>
#include <forward_list>

namespace tktk
{
	class ConstantBufferData
	{
	public:

		ConstantBufferData(ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);
		~ConstantBufferData();

	public:

		void createConstantBufferView(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);

		void updateBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// 全てのアップロード用のバッファを削除する
		void deleteUploadBuffer();

	private:

		ID3D12Resource* m_constantBuffer{ nullptr };
		std::forward_list<ID3D12Resource*> m_uploadBufferList{};
	};
}
#endif // !CONSTANT_BUFFER_DATA_H_