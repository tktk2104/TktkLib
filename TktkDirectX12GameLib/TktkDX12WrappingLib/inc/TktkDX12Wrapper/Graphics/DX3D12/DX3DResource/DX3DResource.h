#ifndef DX_3D_RESOURCE_H_
#define DX_3D_RESOURCE_H_

#include "DX3DResourceInitParam.h"
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

		DX3DResource(const DX3DResourceInitParam& initParam);

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
		void createRenderTargetBuffer(unsigned int id, IDXGISwapChain1* swapChain, unsigned int backBufferIndex);

		// 深度ステンシルバッファを作る
		void createDepthStencilBuffer(unsigned int id, ID3D12Device* device, const tktkMath::Vector2& depthStencilSize);

		// 定数、テクスチャのディスクリプタヒープを作る
		void createBasicDescriptorHeap(unsigned int id, ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam);

		// レンダーターゲットのディスクリプタヒープを作る
		void createRtvDescriptorHeap(unsigned int id, ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam);

		// 深度ステンシルビューのディスクリプタヒープを作る
		void createDsvDescriptorHeap(unsigned int id, ID3D12Device* device, const DsvDescriptorHeapInitParam& initParam);

		// gpu優先でテクスチャを作る
		void gpuPriorityCreateTextureBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// gpu優先でテクスチャをロードする
		void gpuPriorityLoadTextureBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const std::string& texDataPath);

	public: /* リソース更新系処理 */

		// 指定の定数バッファを更新する
		void updateConstantBuffer(unsigned int id, ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// 指定のレンダーターゲットビューを指定の色でクリアする
		void clearRenderTarget(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int rtvLocationIndex, const tktkMath::Color& color);

		// 全てのデプスステンシルビューをクリアする
		void clearDepthStencilViewAll(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);

	public: /* リソース情報取得系処理 */

		// 指定のテクスチャのサイズを取得する
		const tktkMath::Vector3& getTextureSize(unsigned int id) const;

	public: /* 描画準備 */

		// 指定のレンダーターゲットをコマンドリストに設定する
		void setRenderTarget(unsigned int rtvDescriptorHeapId, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount);

		// 指定のレンダーターゲットと深度ステンシルビューをコマンドリストに設定する
		void setRenderTargetAndDepthStencil(unsigned int rtvDescriptorHeapId, unsigned int dsvDescriptorHeapId, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount);

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

		// レンダーターゲットバッファををレンダーターゲット状態にする
		void useRenderTargetBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);

		// レンダーターゲットバッファをプリセット状態にする
		void unUseRenderTargetBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);

	private:

		Viewport			m_viewport;
		ScissorRect			m_scissorRect;
		GraphicsPipeLine	m_graphicsPipeLine;
		DescriptorHeap		m_descriptorHeap;
		BufferResource		m_bufferResource;
	};
}
#endif // !DX_3D_RESOURCE_H_