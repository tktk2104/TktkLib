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
	// DirectX12のリソースを管理するクラス
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
		void createCBuffer(unsigned int id, ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// レンダーターゲットバッファを作る
		void createRtBuffer(unsigned int id, ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);

		// スワップチェーンからレンダーターゲットバッファを取得する
		void createRtBuffer(unsigned int id, IDXGISwapChain1* swapChain, unsigned int backBufferIndex);

		// 深度ステンシルバッファを作る
		void createDsBuffer(unsigned int id, ID3D12Device* device, const DepthStencilBufferInitParam& initParam);

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
		void updateCBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// 全てのアップロード用のバッファを削除する
		void deleteUploadBufferAll();

		// 指定のレンダーターゲットビューを指定の色でクリアする
		void clearRtv(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int rtvLocationIndex, const tktkMath::Color& color);

		// 全てのデプスステンシルビューをクリアする
		void clearDsvAll(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);

	public: /* リソース情報取得系処理 */

		// 指定のバッファのテクスチャとしてのサイズを取得する（ピクセル）
		const tktkMath::Vector3& getTextureBufferSizePx(unsigned int id) const;
		const tktkMath::Vector2& getDsBufferSizePx(unsigned int id) const;
		const tktkMath::Vector2& getRtBufferSizePx(unsigned int id) const;

		// 指定のレンダーターゲット用のディスクリプタヒープが使用しているレンダーターゲットバッファーのIDを取得する
		const std::vector<unsigned int>& getRtvDescriptorHeapUseBufferIdArray(unsigned int id) const;

		// 指定の深度書き込み用のディスクリプタヒープが使用している深度バッファーのIDを取得する
		const std::vector<unsigned int>& getDsvDescriptorHeapUseBufferIdArray(unsigned int id) const;

	public: /* 描画準備 */

		// レンダーターゲットビューをコマンドリストに設定する
		void setRtv(unsigned int rtvDescriptorHeapId, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount);

		// レンダーターゲットビューと深度ステンシルビューをコマンドリストに設定する
		void setRtvAndDsv(unsigned int rtvDescriptorHeapId, unsigned int dsvDescriptorHeapId, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount);

		// 深度ステンシルビューをコマンドリストに設定する
		// ※レンダーターゲットビューは設定できない
		void setOnlyDsv(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList);

		// バックバッファービューを設定する
		void setBackBufferView(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int backBufferIndex);

		// バックバッファービューと深度ステンシルビューを設定する
		void setBackBufferViewAndDsv(unsigned int dsvDescriptorHeapId, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int backBufferIndex);

		// 指定のレンダーターゲット用のディスクリプタヒープが使用しているレンダーターゲットバッファの書き込み後処理を行う
		void unSetRtv(unsigned int rtvDescriptorHeapId, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount);

		// 指定の深度書き込み用のディスクリプタヒープが使用している深度バッファの書き込み後処理を行う
		void unSetDsv(unsigned int dsvDescriptorHeapId, ID3D12GraphicsCommandList* commandList);

		// バックバッファをレンダーターゲット状態にする
		// TODO : 「unsigned int id」を「unsigned int backBufferIndex」に変更する
		void beginWriteBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);

		// バックバッファをプリセット状態にする
		// TODO : 「unsigned int id」を「unsigned int backBufferIndex」に変更する
		void endWriteBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);

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

		// 引数のバッファ情報が定数バッファであれば定数バッファビューを作り、そうでなければエラーを吐く
		void createBasicDescriptorCbv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle, const BasicDescriptorParam& useBufferParam);

		// 引数のバッファ情報がシェーダーリソースになれるバッファであればシェーダーリソースビューを作り、そうでなければエラーを吐く
		void createBasicDescriptorSrv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle, const BasicDescriptorParam& useBufferParam);

	private:

		SystemResourceIdGetter	m_sysResIdGetter;

		Viewport				m_viewport;
		ScissorRect				m_scissorRect;
		GraphicsPipeLine		m_graphicsPipeLine;
		DescriptorHeap			m_descriptorHeap;
		BufferResource			m_bufferResource;
	};
}
#endif // !DX_3D_RESOURCE_H_