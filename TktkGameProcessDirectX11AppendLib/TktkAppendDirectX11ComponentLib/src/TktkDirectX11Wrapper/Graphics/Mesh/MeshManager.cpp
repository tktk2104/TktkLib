#include "TktkDirectX11Wrapper/Graphics/Mesh/MeshManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	CfpPtr<MeshAssets> MeshManager::m_assetsPtr;

	void MeshManager::setUp()
	{
		m_assetsPtr = ComponentFrameworkProcessor::addClass(true, new MeshAssets());
	}

	void MeshManager::createImpl(int id, const VertexBufferInitParams & vertexBufferParams, const IndexBufferInitParams & indexBufferParams)
	{
		m_assetsPtr->create(id, vertexBufferParams, indexBufferParams);
	}

	void MeshManager::eraseImpl(int id)
	{
		m_assetsPtr->erase(id);
	}

	MeshData * MeshManager::getDataPtrImpl(int id)
	{
		return m_assetsPtr->getDataPtr(id);
	}

	void MeshManager::clear()
	{
		m_assetsPtr->clear();
	}
}