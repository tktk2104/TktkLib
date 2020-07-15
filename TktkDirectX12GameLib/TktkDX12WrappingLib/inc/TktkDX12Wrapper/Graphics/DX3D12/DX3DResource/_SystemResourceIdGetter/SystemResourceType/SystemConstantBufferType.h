#ifndef SYSTEM_CONSTANT_BUFFER_TYPE_H_
#define SYSTEM_CONSTANT_BUFFER_TYPE_H_

namespace tktk
{
	constexpr unsigned int SystemConstantBufferNum = 6U;

	enum class SystemConstantBufferType
	{
		Sprite				= 0U,
		MeshTransform		= 1U,
		MeshShadowMap		= 2U,
		BoneMatCbuffer		= 3U,
		BasicMeshLight		= 4U,
		BasicMeshMaterial	= 5U
	};
}
#endif // !SYSTEM_CONSTANT_BUFFER_TYPE_H_