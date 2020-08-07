#ifndef SYSTEM_VERTEX_BUFFER_TYPE_H_
#define SYSTEM_VERTEX_BUFFER_TYPE_H_

namespace tktk
{
	// システムで使用している頂点バッファの数
	constexpr unsigned int SystemVertexBufferNum = 3U;

	// システムで使用している頂点バッファの種類
	enum class SystemVertexBufferType
	{
		Sprite = 0U,
		Line2D,
		Sphere
	};
}
#endif // !SYSTEM_VERTEX_BUFFER_TYPE_H_