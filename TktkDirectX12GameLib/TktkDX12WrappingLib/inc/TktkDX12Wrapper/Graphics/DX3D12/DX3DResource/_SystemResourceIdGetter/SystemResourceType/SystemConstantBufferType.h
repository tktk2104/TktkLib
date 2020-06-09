#ifndef SYSTEM_CONSTANT_BUFFER_TYPE_H_
#define SYSTEM_CONSTANT_BUFFER_TYPE_H_

namespace tktk
{
	constexpr unsigned int SystemConstantBufferNum = 3U;

	enum class SystemConstantBufferType
	{
		Sprite				= 0U,
		BasicMesh			= 1U,
		BasicMeshBoneMat	= 2U,
	};
}
#endif // !SYSTEM_CONSTANT_BUFFER_TYPE_H_