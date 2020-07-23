#ifndef SYSTEM_CBUFFER_TYPE_H_
#define SYSTEM_CBUFFER_TYPE_H_

namespace tktk
{
	// システムで使用している定数バッファの数
	constexpr unsigned int SystemCBufferNum = 6U;

	// システムで使用している定数バッファの種類
	enum class SystemCBufferType
	{
		Sprite				= 0U,
		MeshTransform		= 1U,
		MeshShadowMap		= 2U,
		BoneMatCbuffer		= 3U,
		Light				= 4U,
		BasicMeshMaterial	= 5U
	};
}
#endif // !SYSTEM_CBUFFER_TYPE_H_