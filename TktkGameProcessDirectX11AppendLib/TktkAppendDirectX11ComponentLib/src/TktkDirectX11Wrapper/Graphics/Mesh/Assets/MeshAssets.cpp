#include "TktkDirectX11Wrapper/Graphics/Mesh/Assets/MeshAssets.h"

namespace tktk
{
	MeshAssets::~MeshAssets()
	{
		clear();
	}

	void MeshAssets::create(
		int id,
		D3D_PRIMITIVE_TOPOLOGY primitiveTopology,
		const VertexBufferInitParams & vertexBufferParams,
		const IndexBufferInitParams & indexBufferParams,
		const MaterialSlotsInitParams & materialSlotsParams
	)
	{
		erase(id);

		m_assets.emplace(
			std::piecewise_construct,
			std::forward_as_tuple(id),
			std::forward_as_tuple(primitiveTopology, vertexBufferParams, indexBufferParams, materialSlotsParams)
		);
	}

	void MeshAssets::erase(int id)
	{
		auto eraseNode = m_assets.find(id);
		if (eraseNode == std::end(m_assets)) return;
		m_assets.erase(id);
	}

	void MeshAssets::clear()
	{
		m_assets.clear();
	}

	MeshData * MeshAssets::getDataPtr(int id)
	{
		return &m_assets.at(id);
	}
}