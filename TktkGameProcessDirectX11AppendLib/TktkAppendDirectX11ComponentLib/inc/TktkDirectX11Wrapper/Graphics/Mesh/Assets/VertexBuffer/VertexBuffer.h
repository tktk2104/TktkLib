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

		// コピー禁止
		VertexBuffer(const VertexBuffer& other) = delete;
		VertexBuffer& operator = (const VertexBuffer& other) = delete;

	public:

		// 頂点バッファをレンダリングパイルラインに設定する
		void setBuffer() const;

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
