#ifndef INDEX_BUFFER_H_
#define INDEX_BUFFER_H_

#include <vector>
#include <d3d11.h>
#include "../_MeshInitParams/IndexBufferInitParams.h"

namespace tktk
{
	class IndexBuffer
	{
	public:

		// 意図的に“explicit”を外している
		IndexBuffer(const IndexBufferInitParams& params);
		~IndexBuffer();

		IndexBuffer(const IndexBuffer& other) = delete;
		IndexBuffer& operator = (const IndexBuffer& other) = delete;

	public:

		// インデックスバッファのポインタを取得する
		ID3D11Buffer* getBufferPtr() const;

	private:

		// インデックスバッファのポインタ
		ID3D11Buffer* m_bufferPtr{ nullptr };
	};
}
#endif // !INDEX_BUFFER_H_
