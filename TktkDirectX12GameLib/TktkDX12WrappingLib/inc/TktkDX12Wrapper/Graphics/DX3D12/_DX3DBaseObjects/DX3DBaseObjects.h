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
	// DirectX12の描画を行うためのメインマネージャー
	class DX3DBaseObjects
	{
	public:

		DX3DBaseObjects(const DX3DBaseObjectsInitParam& initParam, HWND hwnd, const tktkMath::Vector2& windowSize, const tktkMath::Color& backGroundColor);
		~DX3DBaseObjects();

	public: /* 描画開始、終了処理 */

		// 描画開始
		void beginDraw();

		// 描画終了
		void endDraw();

	public: /* リソース作成、ロード処理 */

		// ルートシグネチャを作る
		void createRootSignature(unsigned int id, const RootSignatureInitParam& initParam);

		// パイプラインステートを作る
		void createPipeLineState(unsigned int id, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath);

		// 頂点バッファを作る
		void createVertexBuffer(unsigned int id, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);

		// インデックスバッファを作る
		void createIndexBuffer(unsigned int id, const std::vector<unsigned short>& indices);

		// 定数バッファを作る
		void createCBuffer(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// レンダーターゲットバッファを作る
		void createRtBuffer(unsigned int id, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);

		// 深度ステンシルバッファを作る
		void createDsBuffer(unsigned int id, const DepthStencilBufferInitParam& initParam);

		// 定数、テクスチャのディスクリプタヒープを作る
		void createBasicDescriptorHeap(unsigned int id, const BasicDescriptorHeapInitParam& initParam);

		// レンダーターゲットのディスクリプタヒープを作る
		void createRtvDescriptorHeap(unsigned int id, const RtvDescriptorHeapInitParam& initParam);

		// 深度ステンシルビューのディスクリプタヒープを作る
		void createDsvDescriptorHeap(unsigned int id, const DsvDescriptorHeapInitParam& initParam);

		// cpu優先でテクスチャを作る
		void cpuPriorityCreateTextureBuffer(unsigned int id, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// gpu優先でテクスチャを作る
		void gpuPriorityCreateTextureBuffer(unsigned int id, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// cpu優先でテクスチャをロードする
		void cpuPriorityLoadTextureBuffer(unsigned int id, const std::string& texDataPath);

		// gpu優先でテクスチャをロードする
		void gpuPriorityLoadTextureBuffer(unsigned int id, const std::string& texDataPath);

	public: /* リソース更新処理 */

		// 背景色を設定する
		void setBackGroundColor(const tktkMath::Color& backGroundColor);

		// 指定の定数バッファを更新する
		void updateCBuffer(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// 指定のレンダーターゲットビューを指定の色でクリアする
		void clearRtv(unsigned int id, unsigned int rtvLocationIndex, const tktkMath::Color& color);

	public: /* リソース情報取得処理 */

		// 指定のテクスチャのサイズを取得する（ピクセル）
		const tktkMath::Vector3& getTextureBufferSizePx(unsigned int id) const;
		const tktkMath::Vector2& getDsBufferSizePx(unsigned int id) const;
		const tktkMath::Vector2& getRtBufferSizePx(unsigned int id) const;

	public: /* リソースをコマンドリストに登録する処理 */

		// 指定のレンダーターゲット用のディスクリプタヒープをコマンドリストに設定する
		void setRtv(unsigned int rtvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount);

		// 指定の（レンダーターゲットと深度ステンシルビュー）用のディスクリプタヒープ２つをコマンドリストに設定する
		void setRtvAndDsv(unsigned int rtvDescriptorHeapId, unsigned int dsvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount);

		// 指定の深度ステンシルビュー用のディスクリプタヒープをコマンドリストに設定する（※レンダーターゲットは設定できない）
		void setOnlyDsv(unsigned int id);

		// バックバッファーを設定する
		void setBackBufferView();

		// バックバッファーと深度ステンシルビューを設定する
		void setBackBufferViewAndDsv(unsigned int dsvDescriptorHeapId);

		// 指定のレンダーターゲット用のディスクリプタヒープが使用しているレンダーターゲットバッファの書き込み後処理を行う
		void unSetRtv(unsigned int rtvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount);

		// 指定の深度書き込み用のディスクリプタヒープが使用している深度バッファの書き込み後処理を行う
		void unSetDsv(unsigned int dsvDescriptorHeapId);

		// 指定のビューポートをコマンドリストに設定する
		void setViewport(unsigned int id);

		// 指定のシザー矩形をコマンドリストに設定する
		void setScissorRect(unsigned int id);

		// 指定のパイプラインステートをコマンドリストに設定する
		void setPipeLineState(unsigned int id);

		// 指定の頂点バッファをコマンドリストに設定する
		void setVertexBuffer(unsigned int id);

		// 指定のインデックスバッファをコマンドリストに設定する
		void setIndexBuffer(unsigned int id);

		// 指定のディスクリプタヒープの配列をコマンドリストに設定する
		void setDescriptorHeap(const std::vector<DescriptorHeapParam>& heapParamArray);

		// プリミティブトポロジを設定する
		void setPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY topology);

	public: /* ドローコール、その他処理 */

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

	public: /* デフォルトのリソースを使うためのIDを取得する */

		// デフォルトのビューポートIDを取得する
		unsigned int getSystemId(SystemViewportType type) const;

		// デフォルトのシザー矩形IDを取得する
		unsigned int getSystemId(SystemScissorRectType type) const;

		// デフォルトの頂点バッファIDを取得する
		unsigned int getSystemId(SystemVertexBufferType type) const;

		// デフォルトのインデックスバッファIDを取得する
		unsigned int getSystemId(SystemIndexBufferType type) const;

		// デフォルトの定数バッファIDを取得する
		unsigned int getSystemId(SystemConstantBufferType type) const;

		// デフォルトのテクスチャバッファIDを取得する
		unsigned int getSystemId(SystemTextureBufferType type) const;

		// デフォルトのレンダーターゲットバッファIDを取得する
		unsigned int getSystemId(SystemRenderTargetBufferType type) const;

		// デフォルトの深度ステンシルバッファIDを取得する
		unsigned int getSystemId(SystemDepthStencilBufferType type) const;

		// デフォルトの通常のディスクリプタヒープIDを取得する
		unsigned int getSystemId(SystemBasicDescriptorHeapType type) const;

		// デフォルトのレンダーターゲット用のディスクリプタヒープIDを取得する
		unsigned int getSystemId(SystemRtvDescriptorHeapType type) const;

		// デフォルトの深度ステンシル用のディスクリプタヒープIDを取得する
		unsigned int getSystemId(SystemDsvDescriptorHeapType type) const;

		// デフォルトのルートシグネチャIDを取得する
		unsigned int getSystemId(SystemRootSignatureType type) const;

		// デフォルトのパイプラインステートIDを取得する
		unsigned int getSystemId(SystemPipeLineStateType type) const;

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