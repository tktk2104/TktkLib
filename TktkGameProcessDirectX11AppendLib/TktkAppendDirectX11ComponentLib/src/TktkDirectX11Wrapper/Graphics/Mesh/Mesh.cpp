#include "TktkDirectX11Wrapper/Graphics/Mesh/Mesh.h"

#include <stdexcept>
#include "TktkDirectX11Wrapper/Graphics/Mesh/MeshManager.h"

namespace tktk
{
	void Mesh::createImpl(
		int id,
		D3D_PRIMITIVE_TOPOLOGY primitiveTopology,
		const VertexBufferInitParams & vertexBufferParams,
		const IndexBufferInitParams & indexBufferParams,
		const MaterialSlotsInitParams & materialSlotsParams
	)
	{
		if (id <= 0)
		{
			throw std::runtime_error("MeshId Fraud Value");
		}
		MeshManager::create(
			id,
			primitiveTopology,
			vertexBufferParams,
			indexBufferParams,
			materialSlotsParams
		);
	}

	void Mesh::eraseImpl(int id)
	{
		if (id <= 0)
		{
			throw std::runtime_error("MeshId Fraud Value");
		}
		MeshManager::erase(id);
	}

	MeshData * Mesh::getDataPtrImpl(int id)
	{
		return  MeshManager::getDataPtr(id);
	}
}