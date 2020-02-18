#include "TktkDirectX11Wrapper/Graphics/Mesh/Mesh.h"

#include <stdexcept>
#include "TktkDirectX11Wrapper/Graphics/Mesh/MeshManager.h"

namespace tktk
{
	void Mesh::create(
		int id,
		const VertexBufferInitParams & vertexBufferParams,
		const IndexBufferInitParams & indexBufferParams
	)
	{
		if (id <= 0)
		{
			throw std::runtime_error("MeshId Fraud Value");
		}
		MeshManager::create(
			id,
			vertexBufferParams,
			indexBufferParams
		);
	}

	void Mesh::erase(int id)
	{
		if (id <= 0)
		{
			throw std::runtime_error("MeshId Fraud Value");
		}
		MeshManager::erase(id);
	}

	MeshData * Mesh::getDataPtr(int id)
	{
		return  MeshManager::getDataPtr(id);
	}
}