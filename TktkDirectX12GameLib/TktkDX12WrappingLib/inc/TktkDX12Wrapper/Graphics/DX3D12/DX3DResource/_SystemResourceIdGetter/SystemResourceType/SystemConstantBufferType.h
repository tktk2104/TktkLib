#ifndef SYSTEM_CONSTANT_BUFFER_TYPE_H_
#define SYSTEM_CONSTANT_BUFFER_TYPE_H_

namespace tktk
{
	constexpr unsigned int SystemConstantBufferNum = 2U;

	enum class SystemConstantBufferType
	{
		Sprite		= 0U,
		BasicMesh	= 1U
	};
}
#endif // !SYSTEM_CONSTANT_BUFFER_TYPE_H_