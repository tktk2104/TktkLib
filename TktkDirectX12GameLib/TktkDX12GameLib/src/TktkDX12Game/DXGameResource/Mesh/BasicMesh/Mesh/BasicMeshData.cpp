#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Mesh/BasicMeshData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/BasicMeshShadowMapCbufferData.h"

namespace tktk
{
	BasicMeshData::BasicMeshData(const BasicMeshInitParam& initParam)
		: m_useVertexBufferId(initParam.useVertexBufferId)
		, m_useIndexBufferId(initParam.useIndexBufferId)
		, m_indexNum(initParam.indexNum)
		, m_materialSlots(initParam.materialSlots)
	{
	}

	void BasicMeshData::writeShadowMap(const MeshWriteShadowFuncBaseArgs& baseArgs)
	{
		// 通常メッシュ版シャドウマップ描画用の定数バッファを更新する
		updateShadowMapCbuffer(baseArgs);

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
		MeshMaterialDrawFuncArgs materialDrawFuncArgs{};
		materialDrawFuncArgs.useVertexBufferId		= m_useVertexBufferId;
		materialDrawFuncArgs.useIndexBufferId		= m_useIndexBufferId;

		for (const auto& node : m_materialSlots)
		{
			materialDrawFuncArgs.indexBufferStartPos = node.indexBufferStartPos;
			materialDrawFuncArgs.indexBufferUseCount = node.indexBufferUseCount;
		
			DX12GameManager::drawBasicMeshMaterial(node.useMaterialId, baseArgs, materialDrawFuncArgs);
		}
	}

	void BasicMeshData::updateShadowMapCbuffer(const MeshWriteShadowFuncBaseArgs& baseArgs)
	{
		BasicMeshShadowMapCbufferData cbufferData{};

		cbufferData.worldMatrix = baseArgs.worldMatrix;
		cbufferData.viewMatrix = baseArgs.viewMatrix;
		cbufferData.projectionMatrix = baseArgs.projectionMatrix;

		for (unsigned int i = 0; i < 128U; i++)
		{
			cbufferData.boneMatrix[i] = baseArgs.boneMatrix[i];
		}

		DX12GameManager::updateConstantBuffer(DX12GameManager::getSystemId(SystemConstantBufferType::BasicMeshShadowMap), cbufferData);
	}
}