#include "TktkDX12Game/Mesh/BasicMesh/BasicMeshMaterialData.h"

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
	}

	void BasicMeshMaterialData::drawBasicMesh(const MeshDrawFuncBaseArgs& baseArgs)
	{
		BasicMeshConstantBufferData constantBufferData;

		constantBufferData.worldMatrix		= baseArgs.worldMatrix;
		constantBufferData.viewMatrix		= baseArgs.viewMatrix;
		constantBufferData.projectionMatrix	= baseArgs.projectionMatrix;
		constantBufferData.boneMatrix		= baseArgs.boneMatrix;

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
		DX12GameManager::setDescriptorHeap({ { DescriptorHeapType::basic, 2U } });
		DX12GameManager::setPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		DX12GameManager::setVertexBuffer(2U);
		DX12GameManager::setIndexBuffer(2U);
		DX12GameManager::drawIndexedInstanced(4U, 1U, 0U, 0U, 0U);
	}
}