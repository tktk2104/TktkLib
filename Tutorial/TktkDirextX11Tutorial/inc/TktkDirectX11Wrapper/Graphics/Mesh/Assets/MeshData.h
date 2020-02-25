#ifndef MESH_DATA_H_
#define MESH_DATA_H_

#include "VertexBuffer/VertexBuffer.h"
#include "IndexBuffer/IndexBuffer.h"

#include "SystemMeshId.h"

namespace tktk
{
	class MeshData
	{
	public:

		MeshData(
			const VertexBufferInitParams& vertexBufferParams,
			const IndexBufferInitParams& indexBufferParams
		);
		~MeshData();

		MeshData(const MeshData& other) = delete;
		MeshData& operator = (const MeshData& other) = delete;

	public:

		const VertexBuffer& getVertexBuffer() const;

		const IndexBuffer& getIndexBuffer() const;

	private:

		VertexBuffer m_vertexBuffer;
		IndexBuffer m_indexBuffer;
	};
}
#endif // !MESH_DATA_H_
