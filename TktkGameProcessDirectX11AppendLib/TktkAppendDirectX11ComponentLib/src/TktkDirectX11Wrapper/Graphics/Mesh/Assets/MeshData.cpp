#include "TktkDirectX11Wrapper/Graphics/Mesh/Assets/MeshData.h"

#include <algorithm>

namespace tktk
{
	MeshData::MeshData(
		const VertexBufferInitParams & vertexBufferParams,
		const IndexBufferInitParams & indexBufferParams
	)
		: m_vertexBuffer(vertexBufferParams)
		, m_indexBuffer(indexBufferParams)
	{
	}

	MeshData::~MeshData()
	{
	}

	const VertexBuffer & MeshData::getVertexBuffer() const
	{
		return m_vertexBuffer;
	}

	const IndexBuffer & MeshData::getIndexBuffer() const
	{
		return m_indexBuffer;
	}
}