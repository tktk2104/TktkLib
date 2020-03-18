#include "TktkDirectX11Wrapper/Graphics/Mesh/Assets/MeshData.h"

#include <algorithm>
#include "TktkDirectX11Wrapper/Graphics/Screen/Screen.h"

namespace tktk
{
	MeshData::MeshData(
		D3D_PRIMITIVE_TOPOLOGY primitiveTopology,
		const VertexBufferInitParams & vertexBufferParams,
		const IndexBufferInitParams & indexBufferParams,
		const MaterialSlotsInitParams & materialSlotsParams
	)
		: m_primitiveTopology(primitiveTopology)
		, m_vertexBuffer(vertexBufferParams)
		, m_indexBuffer(indexBufferParams)
		, m_materialSlots(materialSlotsParams)
	{
	}

	void MeshData::setPrimitiveTopology() const
	{
		Screen::getDeviceContextPtr()->IASetPrimitiveTopology(m_primitiveTopology);
	}

	void MeshData::setVertexAndIndexBuffer() const
	{
		m_vertexBuffer.setBuffer();
		m_indexBuffer.setBuffer();
	}

	unsigned int MeshData::getMaterialSlotCount() const
	{
		return m_materialSlots.getSlotsCount();
	}

	const Subset & MeshData::getSubset(unsigned int slotIndex) const
	{
		return m_materialSlots.getSubset(slotIndex);
	}
}