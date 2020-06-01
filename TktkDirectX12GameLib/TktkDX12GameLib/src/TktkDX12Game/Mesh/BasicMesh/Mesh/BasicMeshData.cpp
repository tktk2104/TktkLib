#include "TktkDX12Game/Mesh/BasicMesh/Mesh/BasicMeshData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	BasicMeshData::BasicMeshData(const BasicMeshInitParam& initParam)
		: m_useVertexBufferId(initParam.useVertexBufferId)
		, m_useIndexBufferId(initParam.useIndexBufferId)
		, m_materialSlots(initParam.materialSlots)
	{
	}

	void BasicMeshData::drawMesh(const MeshDrawFuncBaseArgs& baseArgs)
	{
		DX12GameManager::setBackBufferAndDepthStencil(DX12GameManager::getSystemId(SystemDepthStencilBufferType::Basic));

		MeshMaterialDrawFuncArgs materialDrawFuncArgs{};

		materialDrawFuncArgs.useVertexBufferId = m_useVertexBufferId;
		materialDrawFuncArgs.useIndexBufferId = m_useIndexBufferId;

		for (const auto& node : m_materialSlots)
		{
			materialDrawFuncArgs.indexBufferStartPos = node.indexBufferStartPos;
			materialDrawFuncArgs.indexBufferUseCount = node.indexBufferUseCount;

			DX12GameManager::drawBasicMeshMaterial(node.useMaterialId, baseArgs, materialDrawFuncArgs);
		}

		DX12GameManager::setBackBuffer();
	}
}