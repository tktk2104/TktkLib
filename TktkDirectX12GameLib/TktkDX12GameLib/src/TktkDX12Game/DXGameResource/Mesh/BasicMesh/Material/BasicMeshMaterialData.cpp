#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Material/BasicMeshMaterialData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/BasicMeshConstantBufferData.h"

namespace tktk
{
	BasicMeshMaterialData::BasicMeshMaterialData(const BasicMeshMaterialInitParam& initParam)
		: m_createDescriptorHeapId(initParam.createDescriptorHeapId)
		, m_materialAmbient(initParam.materialAmbient)
		, m_materialDiffuse(initParam.materialDiffuse)
		, m_materialSpecular(initParam.materialSpecular)
		, m_materialEmissive(initParam.materialEmissive)
		, m_materialShiniess(initParam.materialShiniess)
	{
		// ディスクリプタヒープを作る
		BasicDescriptorHeapInitParam descriptorHeapInitParam{};
		descriptorHeapInitParam.m_shaderVisible = true;
		descriptorHeapInitParam.m_descriptorParamArray.resize(3U);
		descriptorHeapInitParam.m_descriptorParamArray.at(0U).type	= BasicDescriptorType::textureBuffer;
		descriptorHeapInitParam.m_descriptorParamArray.at(0U).id	= initParam.useAlbedoMapTextureId;
		descriptorHeapInitParam.m_descriptorParamArray.at(1U).type	= BasicDescriptorType::constantBuffer;
		descriptorHeapInitParam.m_descriptorParamArray.at(1U).id	= DX12GameManager::getSystemId(SystemConstantBufferType::BasicMesh);
		descriptorHeapInitParam.m_descriptorParamArray.at(2U).type	= BasicDescriptorType::constantBuffer;
		descriptorHeapInitParam.m_descriptorParamArray.at(2U).id	= DX12GameManager::getSystemId(SystemConstantBufferType::BasicMeshBoneMat);

		DX12GameManager::createBasicDescriptorHeap(m_createDescriptorHeapId, descriptorHeapInitParam);
	}

	void BasicMeshMaterialData::drawUseMaterial(const MeshDrawFuncBaseArgs& baseArgs, const MeshMaterialDrawFuncArgs& materialArgs)
	{
		// 通常メッシュ用の定数バッファを更新する
		updateBasicMeshConstantBuffer(baseArgs);

		// ビューポートを設定する
		DX12GameManager::setViewport(baseArgs.viewportId);

		// シザー矩形を設定する
		DX12GameManager::setScissorRect(baseArgs.scissorRectId);

		// レンダーターゲットと深度ステンシルを設定する（バックバッファーに直で描画する場合は特殊処理）
		if (baseArgs.rtvDescriptorHeapId == DX12GameManager::getSystemId(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::setBackBufferAndDepthStencil(baseArgs.dsvDescriptorHeapId);
		}
		else
		{
			DX12GameManager::setRenderTargetAndDepthStencil(baseArgs.rtvDescriptorHeapId, baseArgs.dsvDescriptorHeapId, 0U, 1U);
		}

		// 通常メッシュ用のパイプラインステートを設定する
		DX12GameManager::setPipeLineState(DX12GameManager::getSystemId(SystemPipeLineStateType::BasicMesh));
		
		// 通常メッシュ用のディスクリプタヒープを設定する
		DX12GameManager::setDescriptorHeap({ { DescriptorHeapType::basic, m_createDescriptorHeapId } });
		
		// トライアングルリストで描画を行う
		DX12GameManager::setPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// 描画で使用する頂点バッファを設定する
		DX12GameManager::setVertexBuffer(materialArgs.useVertexBufferId);

		// 描画で使用するインデックスバッファを設定する
		DX12GameManager::setIndexBuffer(materialArgs.useIndexBufferId);

		// ドローコール
		DX12GameManager::drawIndexedInstanced(materialArgs.indexBufferUseCount, 1U, materialArgs.indexBufferStartPos, 0U, 0U);
	
		// バックバッファ以外に描画していたら使用したレンダーターゲットバッファをシェーダーで使用する状態にする
		if (baseArgs.rtvDescriptorHeapId != DX12GameManager::getSystemId(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::unSetRenderTarget(baseArgs.rtvDescriptorHeapId, 0U, 1U);
		}

		// コマンドリストを実行する
		DX12GameManager::executeCommandList();
	}

	// 通常メッシュ用の定数バッファを更新する
	void BasicMeshMaterialData::updateBasicMeshConstantBuffer(const MeshDrawFuncBaseArgs& baseArgs)
	{
		BasicMeshConstantBufferData constantBufferData;

		constantBufferData.worldMatrix = baseArgs.worldMatrix;
		constantBufferData.viewMatrix = baseArgs.viewMatrix;
		constantBufferData.projectionMatrix = baseArgs.projectionMatrix;

		/*for (unsigned int i = 0; i < 128U; i++)
		{
			constantBufferData.boneMatrix[i] = baseArgs.boneMatrix[i];
		}*/

		constantBufferData.lightAmbient = baseArgs.lightAmbient;
		constantBufferData.lightDiffuse = baseArgs.lightDiffuse;
		constantBufferData.lightSpeqular = baseArgs.lightSpeqular;
		constantBufferData.lightPosition = baseArgs.lightPosition;

		constantBufferData.materialAmbient = m_materialAmbient;
		constantBufferData.materialDiffuse = m_materialDiffuse;
		constantBufferData.materialSpecular = m_materialSpecular;
		constantBufferData.materialEmissive = m_materialEmissive;
		constantBufferData.materialShiniess = m_materialShiniess;

		DX12GameManager::updateConstantBuffer(DX12GameManager::getSystemId(SystemConstantBufferType::BasicMesh), constantBufferData);

		BasicMeshBoneMatrix boneMatBuf;

		for (unsigned int i = 0; i < 128U; i++)
		{
			boneMatBuf.boneMatrix[i] = baseArgs.boneMatrix[i];
		}
		DX12GameManager::updateConstantBuffer(DX12GameManager::getSystemId(SystemConstantBufferType::BasicMeshBoneMat), boneMatBuf);
	}
}