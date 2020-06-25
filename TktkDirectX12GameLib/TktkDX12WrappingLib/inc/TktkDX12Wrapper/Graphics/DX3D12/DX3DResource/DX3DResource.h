#ifndef DX_3D_RESOURCE_H_
#define DX_3D_RESOURCE_H_

#include "DX3DResourceInitParam.h"
#include "_SystemResourceIdGetter/SystemResourceIdGetter.h"
#include "Viewport/Viewport.h"
#include "ScissorRect/ScissorRect.h"
#include "GraphicsPipeLine/GraphicsPipeLine.h"
#include "DescriptorHeap/DescriptorHeap.h"
#include "BufferResource/BufferResource.h"

namespace tktk
{
	class DX3DResource
	{
	public:

		// ※意図的に値をコピーしています
		DX3DResource(DX3DResourceInitParam initParam);

	public: /* 作成、ロード処理 */

		// ビューポートを作る
		void createViewport(unsigned int id, const std::vector<ViewportInitParam>& initParamArray);

		// シザー矩形を作る
		void createScissorRect(unsigned int id, const std::vector<ScissorRectInitParam>& initParamArray);

		// ルートシグネチャを作る
		void createRootSignature(unsigned int id, ID3D12Device* device, const RootSignatureInitParam& initParam);

		// パイプラインステートを作る
		void createPipeLineState(unsigned int id, ID3D12Device* device, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath);

		// 頂点バッファを作る
		void createVertexBuffer(unsigned int id, ID3D12Device* device, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);

		// インデックスバッファを作る
		void createIndexBuffer(unsigned int id, ID3D12Device* device, const std::vector<unsigned short>& indices);

		// 定数バッファを作る
		void createConstantBuffer(unsigned int id, ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// レンダーターゲットバッファを作る
		void createRenderTargetBuffer(unsigned int id, ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);

		// スワップチェーンからレンダーターゲットバッファを取得する
		void createRenderTargetBuffer(unsigned int id, IDXGISwapChain1* swapChain, unsigned int backBufferIndex);

		// 深度ステンシルバッファを作る
		void createDepthStencilBuffer(unsigned int id, ID3D12Device* device, const DepthStencilBufferInitParam& initParam);

		// cpu優先でテクスチャバッファを作る
		void cpuPriorityCreateTextureBuffer(unsigned int id, ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// gpu優先でテクスチャバッファを作る
		void gpuPriorityCreateTextureBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// cpu優先でテクスチャをロードしてバッファを作る
		void cpuPriorityLoadTextureBuffer(unsigned int id, ID3D12Device* device, const std::string& texDataPath);

		// gpu優先でテクスチャをロードしてバッファを作る
		void gpuPriorityLoadTextureBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::string& texDataPath);

		// 定数、テクスチャのディスクリプタヒープを作る
		void createBasicDescriptorHeap(unsigned int id, ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam);

		// レンダーターゲットのディスクリプタヒープを作る
		void createRtvDescriptorHeap(unsigned int id, ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam);

		// 深度ステンシルのディスクリプタヒープを作る
		void createDsvDescriptorHeap(unsigned int id, ID3D12Device* device, const DsvDescriptorHeapInitParam& initParam);

	public: /* リソース更新系処理 */

		// 指定の定数バッファを更新する
		void updateConstantBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// 全てのアップロード用のバッファを削除する
		void deleteUploadBufferAll();

		// 指定のレンダーターゲットビューを指定の色でクリアする
		void clearRenderTargetView(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int rtvLocationIndex, const tktkMath::Color& color);

		// 全てのデプスステンシルビューをクリアする
		void clearDepthStencilViewAll(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);

	public: /* リソース情報取得系処理 */

		// 指定のバッファのテクスチャとしてのサイズを取得する
		const tktkMath::Vector3& getTextureBufferSize(unsigned int id) const;
		const tktkMath::Vector2& getDepthStencilBufferSize(unsigned int id) const;
		const tktkMath::Vector2& getRenderTargetBufferSize(unsigned int id) const;

		// 指定のレンダーターゲット用のディスクリプタヒープが使用しているレンダーターゲットバッファーのIDを取得する
		const std::vector<unsigned int>& getRtvDescriptorHeapUseBufferIdArray(unsigned int id) const;

		// 指定の深度書き込み用のディスクリプタヒープが使用している深度バッファーのIDを取得する
		const std::vector<unsigned int>& getDsvDescriptorHeapUseBufferIdArray(unsigned int id) const;

	public: /* 描画準備 */


		// 指定のレンダーターゲット用のディスクリプタヒープをコマンドリストに設定する
		void setRenderTarget(unsigned int rtvDescriptorHeapId, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount);

		// 指定の（レンダーターゲットと深度ステンシルビュー）用のディスクリプタヒープ２つをコマンドリストに設定する
		void setRenderTargetAndDepthStencil(unsigned int rtvDescriptorHeapId, unsigned int dsvDescriptorHeapId, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount);

		// 指定の深度ステンシルビュー用のディスクリプタヒープをコマンドリストに設定する（※レンダーターゲットは設定できない）
		void setOnlyDepthStencil(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList);

		// バックバッファーを設定する
		void setBackBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int backBufferIndex);

		// バックバッファーと深度ステンシルビューを設定する
		void setBackBufferAndDepthStencil(unsigned int dsvDescriptorHeapId, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int backBufferIndex);

		// 指定のレンダーターゲット用のディスクリプタヒープが使用しているレンダーターゲットバッファの書き込み後処理を行う
		void unSetRenderTarget(unsigned int rtvDescriptorHeapId, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount);

		// 指定の深度書き込み用のディスクリプタヒープが使用している深度バッファの書き込み後処理を行う
		void unSetDepthStencil(unsigned int dsvDescriptorHeapId, ID3D12GraphicsCommandList* commandList);

		// レンダーターゲットバッファををレンダーターゲット状態にする
		void useAsBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);

		// レンダーターゲットバッファをプリセット状態にする
		void unUseAsBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);

		// 指定のビューポートをコマンドリストに設定する
		void setViewport(unsigned int id, ID3D12GraphicsCommandList* commandList);

		// 指定のシザー矩形をコマンドリストに設定する
		void setScissorRect(unsigned int id, ID3D12GraphicsCommandList* commandList);

		// 指定のパイプラインステートをコマンドリストに設定する
		void setPipeLineState(unsigned int id, ID3D12GraphicsCommandList* commandList);

		// 指定の頂点バッファをコマンドリストに設定する
		void setVertexBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);

		// 指定のインデックスバッファをコマンドリストに設定する
		void setIndexBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);

		// 指定のディスクリプタヒープの配列をコマンドリストに設定する
		void setDescriptorHeap(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<DescriptorHeapParam>& heapParamArray);

	public: /* デフォルトのリソースを使うためのIDを取得する */

		template <class SystemResourceType>
		unsigned int getSystemId(SystemResourceType type) const;

	private:

		void createBasicDescriptorCbufferView(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle, const BasicDescriptorParam& useBufferParam);

		void createBasicDescriptorShaderResourceView(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle, const BasicDescriptorParam& useBufferParam);

	private:

		SystemResourceIdGetter	m_sysResIdGetter;

		Viewport				m_viewport;
		ScissorRect				m_scissorRect;
		GraphicsPipeLine		m_graphicsPipeLine;
		DescriptorHeap			m_descriptorHeap;
		BufferResource			m_bufferResource;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	template<class SystemResourceType>
	inline unsigned int DX3DResource::getSystemId(SystemResourceType type) const
	{
		return m_sysResIdGetter.getSystemId(type);
	}
}
#endif // !DX_3D_RESOURCE_H_