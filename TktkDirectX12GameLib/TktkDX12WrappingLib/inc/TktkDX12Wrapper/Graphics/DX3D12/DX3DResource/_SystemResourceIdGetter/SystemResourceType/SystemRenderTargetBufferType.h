#ifndef SYSTEM_RENDER_TARGET_BUFFER_TYPE_H_
#define SYSTEM_RENDER_TARGET_BUFFER_TYPE_H_

namespace tktk
{
	constexpr unsigned int SystemRenderTargetBufferNum = 2U;

	enum class SystemRenderTargetBufferType
	{
		BackBuffer_1	= 0U,
		BackBuffer_2	= 1U,
	};
}
#endif // !SYSTEM_RENDER_TARGET_BUFFER_TYPE_H_