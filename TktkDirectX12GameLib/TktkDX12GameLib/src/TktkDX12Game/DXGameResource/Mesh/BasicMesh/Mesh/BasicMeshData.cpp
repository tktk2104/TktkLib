#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Mesh/BasicMeshData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	BasicMeshData::BasicMeshData(const BasicMeshInitParam& initParam)
		: m_useVertexBufferId(initParam.useVertexBufferId)
		, m_useIndexBufferId(initParam.useIndexBufferId)
		, m_indexNum(initParam.indexNum)
		, m_materialSlots(initParam.materialSlots)
	{
	}

	void BasicMeshData::writeShadowMap()
	{
		// シャドウマップ描画用の深度バッファー“のみ”を設定する
		DX12GameManager::setOnlyDepthStencil(DX12GameManager::getSystemId(SystemDsvDescriptorHeapType::ShadowMap));

		// ビューポートを設定する
		DX12GameManager::setViewport(DX12GameManager::getSystemId(SystemViewportType::Basic));

		// シザー矩形を設定する
		DX12GameManager::setScissorRect(DX12GameManager::getSystemId(SystemScissorRectType::Basic));

		// 通常メッシュ版シャドウマップ描画用のパイプラインステートを設定する
		DX12GameManager::setPipeLineState(DX12GameManager::getSystemId(SystemPipeLineStateType::ShadowMap));

		// 通常メッシュ版シャドウマップ描画用のディスクリプタヒープを設定する
		DX12GameManager::setDescriptorHeap({ { DescriptorHeapType::basic, DX12GameManager::getSystemId(SystemBasicDescriptorHeapType::BasicMeshShadowMap) } });

		// トライアングルリストで描画を行う
		DX12GameManager::setPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// 描画で使用する頂点バッファを設定する
		DX12GameManager::setVertexBuffer(m_useVertexBufferId);

		// 描画で使用するインデックスバッファを設定する
		DX12GameManager::setIndexBuffer(m_useIndexBufferId);

		// ドローコール
		DX12GameManager::drawIndexedInstanced(m_indexNum, 1U, 0U, 0U, 0U);

		// 深度ステンシルバッファーをシェーダーで使える状態にする
		DX12GameManager::unSetDepthStencil(DX12GameManager::getSystemId(SystemDsvDescriptorHeapType::ShadowMap));

		// コマンドリストを実行する
		DX12GameManager::executeCommandList();
	}

	void BasicMeshData::drawMesh(const MeshDrawFuncBaseArgs& baseArgs)
	{
		// ビューポートを設定する
		DX12GameManager::setViewport(baseArgs.viewportId);

		// シザー矩形を設定する
		DX12GameManager::setScissorRect(baseArgs.scissorRectId);

		// 通常メッシュ用のパイプラインステートを設定する
		DX12GameManager::setPipeLineState(DX12GameManager::getSystemId(SystemPipeLineStateType::BasicMesh));

		// トライアングルリストで描画を行う
		DX12GameManager::setPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// 描画で使用する頂点バッファを設定する
		DX12GameManager::setVertexBuffer(m_useVertexBufferId);

		// 描画で使用するインデックスバッファを設定する
		DX12GameManager::setIndexBuffer(m_useIndexBufferId);

		// レンダーターゲットと深度ステンシルを設定する（バックバッファーに直で描画する場合は特殊処理）
		if (baseArgs.rtvDescriptorHeapId == DX12GameManager::getSystemId(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::setBackBufferAndDepthStencil(baseArgs.dsvDescriptorHeapId);
		}
		else
		{
			DX12GameManager::setRenderTargetAndDepthStencil(baseArgs.rtvDescriptorHeapId, baseArgs.dsvDescriptorHeapId, 0U, 1U);
		}

		// マテリアルの数だけ描画する
		for (const auto& node : m_materialSlots)
		{
			// マテリアルの情報を設定する
			DX12GameManager::setMaterialData(node.useMaterialId);

			// ドローコール
			DX12GameManager::drawIndexedInstanced(node.indexBufferUseCount, 1U, node.indexBufferStartPos, 0U, 0U);
		}

		// バックバッファ以外に描画していたら使用したレンダーターゲットバッファをシェーダーで使用する状態にする
		if (baseArgs.rtvDescriptorHeapId != DX12GameManager::getSystemId(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::unSetRenderTarget(baseArgs.rtvDescriptorHeapId, 0U, 1U);
		}

		// 深度ステンシルバッファーをシェーダーで使える状態にする
		DX12GameManager::unSetDepthStencil(baseArgs.dsvDescriptorHeapId);

		// コマンドリストを実行する
		DX12GameManager::executeCommandList();
	}
}