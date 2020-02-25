#ifndef VERTEX_BUFFER_H_
#define VERTEX_BUFFER_H_

#include <d3d11.h>
#include "../_MeshInitParams/VertexBufferInitParams.h"

namespace tktk
{
	class VertexBuffer
	{
	public:

		// 意図的に“explicit”を外している
		VertexBuffer(const VertexBufferInitParams& params);
		~VertexBuffer();

		VertexBuffer(const VertexBuffer& other) = delete;
		VertexBuffer& operator = (const VertexBuffer& other) = delete;

	public:

		// 頂点バッファのポインタを取得する
		ID3D11Buffer* getVertexBufferPtr() const;

		// ストライドを取得する
		unsigned int getStride() const;

		// オフセットを取得する
		unsigned int getOffset() const;


	private:

		// 頂点バッファのポインタ
		ID3D11Buffer* m_vertexBufferPtr{ nullptr };

		// ストライド
		unsigned int m_stride = 0U;

		// オフセット
		unsigned int m_offset = 0U;
	};
}
#endif // !VERTEX_BUFFER_H_
