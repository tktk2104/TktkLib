#ifndef DX3D_BASE_OBJECTS_H_
#define DX3D_BASE_OBJECTS_H_

#include <vector>
#include <d3d12.h>
#include <dxgi1_6.h>
#undef min
#undef max
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include "DX3DBaseObjectsInitParam.h"

#include "../Fence/Fence.h"

#include "../DX3DResource/DX3DResource.h"

namespace tktk
{
	class DX3DBaseObjects
	{
	public:

		DX3DBaseObjects(const DX3DBaseObjectsInitParam& initParam, HWND hwnd, const tktkMath::Vector2& windowSize, const tktkMath::Color& backGroundColor);
		~DX3DBaseObjects();

	public:

		// 描画開始
		void beginDraw();

		// 描画終了
		void endDraw();

	public:

		// ルートシグネチャを作る
		void createRootSignature(unsigned int id, const RootSignatureInitParam& initParam);

		// グラフィックパイプラインステートを作る
		void createGraphicsPipeLineState(unsigned int id, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath);

		// 頂点バッファを作る
		void createVertexBuffer(unsigned int id, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);

		// インデックスバッファを作る
		void createIndexBuffer(unsigned int id, const std::vector<unsigned short>& indices);

		// 定数バッファを作る
		void createConstantBuffer(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// 深度ステンシルバッファを作る
		void createDepthStencilBuffer(unsigned int id, const tktkMath::Vector2& depthStencilSize);

		// 定数、テクスチャのディスクリプタヒープを作る
		void createBasicDescriptorHeap(unsigned int id, const BasicDescriptorHeapInitParam& initParam);

		// 深度ステンシルビューのディスクリプタヒープを作る
		void createDsvDescriptorHeap(unsigned int id, const DsvDescriptorHeapInitParam& initParam);

		// gpu優先でテクスチャをロードする
		void gpuPriorityLoadTextureBuffer(unsigned int id, const TexBufFormatParam& formatParam, const std::string& texDataPath);

	public:

		// 指定の定数バッファを更新する
		void updateConstantBuffer(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// 指定のテクスチャのサイズを取得する
		const tktkMath::Vector3& getTextureSize(unsigned int id) const;

	public:

		// 背景色を設定する
		void setBackGroundColor(const tktkMath::Color& backGroundColor);

		// バックバッファー用のレンダーターゲットをコマンドリストに設定する
		void setBackBufferRenderTarget();

		// バックバッファー用のレンダーターゲットと指定のデプスステンシルビューをコマンドリストに設定する
		void setUseDepthStencilBackBufferRenderTarget(unsigned int dsvDescriptorHeapId);

		// 指定のビューポートをコマンドリストに設定する
		void setViewport(unsigned int id);

		// 指定のシザー矩形をコマンドリストに設定する
		void setScissorRect(unsigned int id);

		// 指定のグラフィックパイプラインステートをコマンドリストに設定する
		void setGraphicsPipeLineState(unsigned int id);

		// 指定の頂点バッファをコマンドリストに設定する
		void setVertexBuffer(unsigned int id);

		// 指定のインデックスバッファをコマンドリストに設定する
		void setIndexBuffer(unsigned int id);

		// 指定のディスクリプタヒープの配列をコマンドリストに設定する
		void setDescriptorHeap(const std::vector<DescriptorHeapParam>& heapParamArray);

		// プリミティブトポロジを設定する
		void setPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY topology);

	public:

		// インデックスを使用してインスタンス描画を行う
		void drawIndexedInstanced(
			unsigned int indexCountPerInstance,
			unsigned int instanceCount,
			unsigned int startIndexLocation,
			unsigned int baseVertexLocation,
			unsigned int startInstanceLocation
		);

		// コマンドリストを実行する
		void executeCommandList();

	private:

		ID3D12Device*				m_device				{ nullptr };
		IDXGIFactory6*				m_factory				{ nullptr };
		ID3D12CommandAllocator*		m_commandAllocator		{ nullptr };
		ID3D12GraphicsCommandList*	m_commandList			{ nullptr };
		ID3D12CommandQueue*			m_commandQueue			{ nullptr };
		IDXGISwapChain1*			m_swapChain				{ nullptr };
		unsigned int				m_curBackBufferIndex	{ 0U };
		Fence						m_fence					{};

		DX3DResource				m_dX3DResource;
		tktkMath::Color				m_backGroundColor{ tktkMath::colorBlue };
	};
}
#endif // !DX3D_BASE_OBJECTS_H_