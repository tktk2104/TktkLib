#ifndef SYSTEM_CONSTANT_BUFFER_TYPE_H_
#define SYSTEM_CONSTANT_BUFFER_TYPE_H_

namespace tktk
{
	constexpr unsigned int SystemConstantBufferNum = 6U;

	enum class SystemConstantBufferType
	{
		Sprite				= 0U,
		MeshTransform		= 1U,
		BoneMatCbuffer		= 2U,
		BasicMeshLight		= 3U,
		BasicMeshMaterial	= 4U
	};
}
#endif // !SYSTEM_CONSTANT_BUFFER_TYPE_H_