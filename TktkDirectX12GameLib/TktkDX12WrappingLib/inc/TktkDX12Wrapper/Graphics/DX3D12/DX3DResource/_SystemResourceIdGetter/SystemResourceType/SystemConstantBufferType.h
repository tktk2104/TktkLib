#ifndef SYSTEM_CONSTANT_BUFFER_TYPE_H_
#define SYSTEM_CONSTANT_BUFFER_TYPE_H_

namespace tktk
{
	constexpr unsigned int SystemConstantBufferNum = 4U;

	enum class SystemConstantBufferType
	{
		Sprite				= 0U,
		BasicMesh			= 1U,
		BasicMeshBoneMat	= 2U,
		BasicMeshShadowMap	= 3U
	};
}
#endif // !SYSTEM_CONSTANT_BUFFER_TYPE_H_