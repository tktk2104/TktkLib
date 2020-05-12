#include "TktkDX12Game/Mesh/BasicMesh/Material/BasicMeshMaterialData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/Mesh/BasicMesh/BasicMeshConstantBufferData.h"

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
		//// ディスクリプタヒープを作る
		//BasicDescriptorHeapInitParam descriptorHeapInitParam{};
		//descriptorHeapInitParam.m_shaderVisible = true;
		//descriptorHeapInitParam.m_descriptorParamArray.resize(1U);
		//descriptorHeapInitParam.m_descriptorParamArray.at(0U).m_type = BasicDescriptorType::constantBuffer;
		//descriptorHeapInitParam.m_descriptorParamArray.at(0U).m_id = 2U;

		// ディスクリプタヒープを作る
		BasicDescriptorHeapInitParam descriptorHeapInitParam{};
		descriptorHeapInitParam.m_shaderVisible = true;
		descriptorHeapInitParam.m_descriptorParamArray.resize(2U);
		descriptorHeapInitParam.m_descriptorParamArray.at(0U).m_type = BasicDescriptorType::textureBuffer;
		descriptorHeapInitParam.m_descriptorParamArray.at(0U).m_id = 0U;
		descriptorHeapInitParam.m_descriptorParamArray.at(1U).m_type = BasicDescriptorType::constantBuffer;
		descriptorHeapInitParam.m_descriptorParamArray.at(1U).m_id = 2U;


		DX12GameManager::createBasicDescriptorHeap(m_createDescriptorHeapId, descriptorHeapInitParam);
	}

	void BasicMeshMaterialData::drawUseMaterial(const MeshDrawFuncBaseArgs& baseArgs, const MeshMaterialDrawFuncArgs& materialArgs)
	{
		BasicMeshConstantBufferData constantBufferData;

		constantBufferData.worldMatrix		= baseArgs.worldMatrix;
		constantBufferData.viewMatrix		= baseArgs.viewMatrix;
		constantBufferData.projectionMatrix	= baseArgs.projectionMatrix;

		/*for (unsigned int i = 0; i < 256U; i++)
		{
			constantBufferData.boneMatrix[i] = baseArgs.boneMatrix[i];
		}*/

		constantBufferData.lightAmbient		= baseArgs.lightAmbient;
		constantBufferData.lightDiffuse		= baseArgs.lightDiffuse;
		constantBufferData.lightSpeqular	= baseArgs.lightSpeqular;
		constantBufferData.lightPosition	= baseArgs.lightPosition;

		constantBufferData.materialAmbient	= m_materialAmbient;
		constantBufferData.materialDiffuse	= m_materialDiffuse;
		constantBufferData.materialSpecular	= m_materialSpecular;
		constantBufferData.materialEmissive	= m_materialEmissive;
		constantBufferData.materialShiniess = m_materialShiniess;

		DX12GameManager::updateConstantBuffer(2U, constantBufferData);

		DX12GameManager::setGraphicsPipeLineState(2U);


		DX12GameManager::setDescriptorHeap({ { DescriptorHeapType::basic, m_createDescriptorHeapId } });
		DX12GameManager::setPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		DX12GameManager::setVertexBuffer(materialArgs.useVertexBufferId);
		DX12GameManager::setIndexBuffer(materialArgs.useIndexBufferId);
		DX12GameManager::drawIndexedInstanced(materialArgs.indexBufferUseCount, 1U, materialArgs.indexBufferStartPos, 0U, 0U);
	}
}